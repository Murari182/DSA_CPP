#!/usr/bin/env node
'use strict';

const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const { spawnSync } = require('node:child_process');
const { pathToFileURL } = require('node:url');
const MarkdownIt = require('markdown-it');
const texmath = require('markdown-it-texmath');
const katex = require('katex');
const anchor = require('markdown-it-anchor');

const repoRoot = path.resolve(__dirname, '..', '..');
const toolRoot = __dirname;
const args = process.argv.slice(2);

function showHelp() {
  console.log(`Convert Markdown files in this repository to PDFs.

Usage:
  node tools/markdown-to-pdf/convert-md-to-pdf.cjs [repo-relative-input] [repo-relative-output]

Install dependencies once:
  npm install --prefix tools/markdown-to-pdf

Defaults:
  Input:  repository root
  Output: repository\\PDFs

When a folder is given, its Markdown files are converted recursively and their
repository-relative paths are preserved in the output folder. Requires Node.js
18+ and Microsoft Edge or Google Chrome. Set EDGE_PATH to use a custom browser
location.`);
}

function isWithin(parent, target) {
  const relative = path.relative(parent, target);
  return relative === '' || (!relative.startsWith(`..${path.sep}`) && relative !== '..' && !path.isAbsolute(relative));
}

function findBrowser() {
  const candidates = [
    process.env.EDGE_PATH,
    process.env.CHROME_PATH,
    process.env.PROGRAMFILES ? path.join(process.env.PROGRAMFILES, 'Microsoft', 'Edge', 'Application', 'msedge.exe') : null,
    process.env['PROGRAMFILES(X86)'] ? path.join(process.env['PROGRAMFILES(X86)'], 'Microsoft', 'Edge', 'Application', 'msedge.exe') : null,
    process.env.LOCALAPPDATA ? path.join(process.env.LOCALAPPDATA, 'Microsoft', 'Edge', 'Application', 'msedge.exe') : null,
    process.env.PROGRAMFILES ? path.join(process.env.PROGRAMFILES, 'Google', 'Chrome', 'Application', 'chrome.exe') : null,
    process.env['PROGRAMFILES(X86)'] ? path.join(process.env['PROGRAMFILES(X86)'], 'Google', 'Chrome', 'Application', 'chrome.exe') : null,
    process.platform === 'darwin' ? '/Applications/Microsoft Edge.app/Contents/MacOS/Microsoft Edge' : null,
    process.platform === 'darwin' ? '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome' : null,
  ].filter(Boolean);

  for (const candidate of candidates) {
    if (fs.existsSync(candidate)) return candidate;
  }

  const commands = process.platform === 'win32'
    ? ['msedge.exe', 'chrome.exe']
    : process.platform === 'darwin'
      ? ['microsoft-edge', 'google-chrome']
      : ['microsoft-edge', 'microsoft-edge-stable', 'google-chrome', 'chromium', 'chromium-browser'];
  const locator = process.platform === 'win32' ? 'where.exe' : 'which';
  for (const command of commands) {
    const result = spawnSync(locator, [command], { encoding: 'utf8', windowsHide: true });
    const located = result.status === 0 && result.stdout ? result.stdout.trim().split(/\r?\n/)[0] : '';
    if (located && fs.existsSync(located)) return located;
  }

  throw new Error('Microsoft Edge or Google Chrome was not found. Install one or set EDGE_PATH to its executable.');
}

function collectMarkdown(inputPath, outputPath) {
  if (!fs.existsSync(inputPath)) throw new Error(`Input does not exist: ${inputPath}`);
  if (!isWithin(repoRoot, inputPath)) {
    throw new Error(`Input must be inside this repository: ${inputPath}`);
  }

  if (fs.statSync(inputPath).isFile()) {
    if (!/\.md$/i.test(inputPath)) throw new Error(`Input file must have a .md extension: ${inputPath}`);
    return [inputPath];
  }
  if (!fs.statSync(inputPath).isDirectory()) throw new Error(`Input is not a file or directory: ${inputPath}`);

  const files = [];
  function walk(directory) {
    for (const entry of fs.readdirSync(directory, { withFileTypes: true })) {
      const fullPath = path.join(directory, entry.name);
      if (entry.isDirectory()) {
        if (entry.name === '.git' || entry.name === 'node_modules' || isWithin(outputPath, fullPath)) continue;
        walk(fullPath);
      } else if (entry.isFile() && /\.md$/i.test(entry.name)) {
        files.push(fullPath);
      }
    }
  }
  walk(inputPath);
  return files.sort();
}

function createMarkdownRenderer() {
  const md = new MarkdownIt({ html: true, linkify: true, typographer: false })
    .use(anchor, { tabIndex: false, permalink: false })
    .use(texmath, {
      engine: katex,
      delimiters: 'dollars',
      katexOptions: { throwOnError: true },
    });
  const defaultFence = md.renderer.rules.fence;
  md.renderer.rules.fence = (tokens, index, options, env, self) => {
    const token = tokens[index];
    const language = (token.info || '').trim().toLowerCase();
    if (language === 'math') {
      return `<div class="math-block">${katex.renderToString(token.content.trim(), {
        displayMode: true,
        throwOnError: true,
      })}</div>\n`;
    }
    if (language === 'mermaid') {
      return `<div class="mermaid">${md.utils.escapeHtml(token.content)}</div>\n`;
    }
    return defaultFence(tokens, index, options, env, self);
  };
  return md;
}

function escapeHtml(text) {
  return String(text).replace(/[&<>"']/g, character => ({
    '&': '&amp;',
    '<': '&lt;',
    '>': '&gt;',
    '"': '&quot;',
    "'": '&#39;',
  }[character]));
}

function createHtml(source, sourcePath, markdown, katexCss, mermaidJs) {
  const baseUri = pathToFileURL(`${path.dirname(sourcePath)}${path.sep}`).href;
  const tableColumns = source.split(/\r?\n/)
    .filter(line => /^\s*\|/.test(line))
    .reduce((maximum, line) => Math.max(maximum, line.split('|').length - 2), 0);
  const orientation = tableColumns >= 8 ? 'landscape' : 'portrait';
  const title = path.basename(sourcePath, path.extname(sourcePath));
  const body = markdown.render(source, { filePath: sourcePath });

  return `<!doctype html>
<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<base href="${baseUri}"><title>${escapeHtml(title)}</title><link rel="stylesheet" href="${katexCss}">
<style>
@page { size: A4 ${orientation}; margin: 15mm 14mm 16mm; }
* { box-sizing: border-box; }
html { color-scheme: light; }
body { margin: 0; color: #172033; background: #fff; font: 10pt/1.5 "Segoe UI", Arial, sans-serif; -webkit-print-color-adjust: exact; print-color-adjust: exact; }
main { max-width: 100%; margin: 0 auto; overflow-wrap: anywhere; }
h1,h2,h3,h4,h5,h6 { color: #12355b; line-height: 1.25; break-after: avoid-page; page-break-after: avoid; }
h1 { font-size: 23pt; border-bottom: 2px solid #d6e2ef; padding-bottom: 5pt; margin-top: 0; }
h2 { font-size: 17pt; margin-top: 24pt; border-bottom: 1px solid #e2e8f0; padding-bottom: 3pt; }
h3 { font-size: 13pt; margin-top: 18pt; }
p,li { orphans: 3; widows: 3; }
blockquote { margin: 10pt 0; padding: 6pt 12pt; border-left: 3px solid #8daac8; background: #f5f8fb; color: #35445a; }
hr { border: 0; border-top: 1px solid #d8e0e9; margin: 18pt 0; }
a { color: #155da8; text-decoration: none; }
code,pre { font-family: Consolas, "Cascadia Mono", "Courier New", monospace; }
code { font-size: .9em; color: #173c66; background: #f1f4f8; padding: 1pt 3pt; border-radius: 2pt; }
pre { overflow-wrap: anywhere; white-space: pre-wrap; background: #f4f6f9; border: 1px solid #e1e6ed; border-radius: 4pt; padding: 8pt 10pt; font-size: 8.3pt; line-height: 1.35; }
pre code { color: #172033; background: transparent; padding: 0; font-size: inherit; }
table { width: 100%; border-collapse: collapse; margin: 10pt 0 14pt; font-size: 8.2pt; line-height: 1.35; }
th,td { border: 1px solid #cbd5e1; padding: 4pt 5pt; vertical-align: top; overflow-wrap: anywhere; }
th { background: #eaf1f8; color: #12355b; font-weight: 700; }
tr { break-inside: avoid-page; }
img { display: block; max-width: 100%; max-height: 245mm; height: auto; margin: 10pt auto; object-fit: contain; break-inside: avoid-page; }
.mermaid { display: block; text-align: center; margin: 12pt auto; break-inside: avoid-page; }
.mermaid svg { display: inline-block; max-width: 100% !important; height: auto !important; }
.math-block { text-align: center; margin: 10pt auto; break-inside: avoid-page; }
.katex-display { max-width: 100%; overflow-x: auto; overflow-y: hidden; }
</style></head><body><main>${body}</main>
<script src="${mermaidJs}"></script>
<script>window.__pdfReady=false;mermaid.initialize({startOnLoad:false,securityLevel:'loose',theme:'default',fontFamily:'Arial'});mermaid.run({querySelector:'.mermaid'}).then(()=>{window.__pdfReady=true}).catch(e=>{document.body.dataset.mermaidError=String(e);console.error(e);window.__pdfReady=true});</script>
</body></html>`;
}

function main() {
  if (args.includes('--help') || args.includes('-h')) {
    showHelp();
    return;
  }
  if (args.length > 2) throw new Error('Too many arguments. Use --help for usage.');

  const inputPath = args[0] ? path.resolve(repoRoot, args[0]) : repoRoot;
  const outputPath = args[1] ? path.resolve(repoRoot, args[1]) : path.join(repoRoot, 'PDFs');
  const sources = collectMarkdown(inputPath, outputPath);
  if (!sources.length) throw new Error(`No Markdown files found under ${inputPath}`);

  const browser = findBrowser();
  const katexCss = pathToFileURL(path.join(toolRoot, 'node_modules', 'katex', 'dist', 'katex.min.css')).href;
  const mermaidJs = pathToFileURL(path.join(toolRoot, 'node_modules', 'mermaid', 'dist', 'mermaid.min.js')).href;
  const markdown = createMarkdownRenderer();
  const temporary = fs.mkdtempSync(path.join(os.tmpdir(), 'markdown-to-pdf-'));
  const failures = [];

  try {
    for (const [index, sourcePath] of sources.entries()) {
      const relativePath = path.relative(repoRoot, sourcePath);
      const outputFile = path.join(outputPath, relativePath.replace(/\.md$/i, '.pdf'));
      const htmlFile = path.join(temporary, `${String(index).padStart(4, '0')}.html`);
      const temporaryPdf = path.join(temporary, `${String(index).padStart(4, '0')}.pdf`);
      const profile = path.join(temporary, `profile-${index}`);
      fs.mkdirSync(path.dirname(outputFile), { recursive: true });

      try {
        const source = fs.readFileSync(sourcePath, 'utf8');
        const html = createHtml(source, sourcePath, markdown, katexCss, mermaidJs);
        fs.writeFileSync(htmlFile, html, 'utf8');
        const browserArgs = [
          '--headless',
          '--disable-gpu',
          '--no-first-run',
          '--no-default-browser-check',
          '--allow-file-access-from-files',
          '--run-all-compositor-stages-before-draw',
          '--virtual-time-budget=12000',
          `--user-data-dir=${profile}`,
          `--print-to-pdf=${temporaryPdf}`,
          '--no-pdf-header-footer',
          pathToFileURL(htmlFile).href,
        ];
        const result = spawnSync(browser, browserArgs, {
          encoding: 'utf8',
          timeout: 120000,
          windowsHide: true,
        });
        if (result.error) throw result.error;
        if (result.status !== 0) throw new Error(result.stderr || result.stdout || `Browser exited with code ${result.status}`);

        const pdf = fs.readFileSync(temporaryPdf);
        if (pdf.subarray(0, 5).toString() !== '%PDF-' || pdf.length < 1000) {
          throw new Error(`Browser did not create a valid PDF (${pdf.length} bytes)`);
        }
        fs.copyFileSync(temporaryPdf, outputFile);
        console.log(`OK ${relativePath} -> ${path.relative(outputPath, outputFile)} (${pdf.length} bytes)`);
      } catch (error) {
        failures.push(`${relativePath}: ${error.message}`);
      }
    }
  } finally {
    fs.rmSync(temporary, { recursive: true, force: true });
  }

  if (failures.length) {
    throw new Error(`Failed to convert ${failures.length} of ${sources.length} Markdown file(s):\n${failures.join('\n')}`);
  }
  console.log(`\nCreated and verified ${sources.length} PDF file(s) in ${outputPath}`);
}

try {
  main();
} catch (error) {
  console.error(error.message);
  process.exitCode = 1;
}
