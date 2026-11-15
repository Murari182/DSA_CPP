# Hashing, Hash Tables & Collision Resolution

A comprehensive module covering hash function construction, direct addressing, open addressing (linear, quadratic, double hashing), separate chaining, cuckoo hashing, load factors, and dynamic rehashing in modern C++17.

---

## Module Overview & Study Guide

| Category | Note Reference | Code Implementation | Key Focus |
|---|---|---|---|
| **Master Overview** | [Hashing_Complete_Notes.md](./Notes/Hashing_Complete_Notes.md) | [hello.cpp](./hello.cpp) | Complete hashing guide, terminology, load factor $ \alpha $ |
| **Hash Functions** | [Hash_Functions_and_Hashing_Techniques.md](./Notes/Hash_Functions_and_Hashing_Techniques.md) | [Hashing without collisions.cpp](./Hashing%20without%20collisions.cpp) | Division, multiplication, mid-square, folding, universal hashing |
| **Separate Chaining** | [Hashing_Complete_Notes.md](./Notes/Hashing_Complete_Notes.md) | [Detailed_Separate Chaining using Linked List.cpp](./Codes/Detailed_Separate%20Chaining%20using%20Linked%20List.cpp) | Linked list buckets, load factor tolerance $ \alpha > 1 $ |
| **Linear Probing** | [Hashing_Complete_Notes.md](./Notes/Hashing_Complete_Notes.md) | [Complete Linear Probing Implementation.cpp](./Codes/Complete%20Linear%20Probing%20Implementation.cpp) | $ h(k, i) = (h(k) + i) \pmod m $, primary clustering |
| **Quadratic Probing** | [Quadratic_Probing_Complete_Guide.md](./Notes/Quadratic_Probing_Complete_Guide.md) | [Quadratic_Probing_Example.cpp](./Codes/Quadratic_Probing_Example.cpp) | $ h(k, i) = (h(k) + c_1 i + c_2 i^2) \pmod m $, secondary clustering |
| **Double Hashing** | [Double_Hashing_Complete_Guide.md](./Notes/Double_Hashing_Complete_Guide.md) | [Double_Hashing_Example.cpp](./Codes/Double_Hashing_Example.cpp) | $ h(k, i) = (h_1(k) + i \cdot h_2(k)) \pmod m $, eliminates clustering |
| **Cuckoo Hashing** | [Cuckoo_Hashing_Complete_Guide.md](./Notes/Cuckoo_Hashing_Complete_Guide.md) | [Codes/Cuckoo_Hashing_Example.cpp](./Codes/Cuckoo_Hashing_Example.cpp) | Two hash functions, guaranteed $ O(1) $ worst-case lookup |
| **Rehashing** | [Rehashing_Complete_Notes_README.md](./Notes/Rehashing_Complete_Notes_README.md) | [Complete Linear Probing Implementation.cpp](./Codes/Complete%20Linear%20Probing%20Implementation.cpp) | Next prime capacity doubling, element migration |

---

## Collision Resolution Strategies

```math
\text{Load Factor } \alpha = \frac{\text{Number of Stored Keys (n)}}{\text{Table Capacity (m)}}
```

### 1. Separate Chaining (Open Hashing)
- Each bucket in the hash table points to a linked list (or dynamic array) of colliding elements.
- **Load Factor:** Can exceed 1 ($ \alpha > 1 $).
- **Average Search:** $ O(1 + \alpha) $.

### 2. Open Addressing (Closed Hashing)
All elements reside directly within the hash table array. If a collision occurs, an alternative probe sequence is traversed:
- **Linear Probing:** $ h(k, i) = (h(k) + i) \pmod m $. Exhibits **Primary Clustering** (long contiguous blocks of occupied slots build up, slowing subsequent probes).
- **Quadratic Probing:** $ h(k, i) = (h(k) + c_1 i + c_2 i^2) \pmod m $. Mitigates primary clustering, but exhibits **Secondary Clustering**.
- **Double Hashing:** $ h(k, i) = (h_1(k) + i \cdot h_2(k)) \pmod m $. The step size depends on the key itself; virtually eliminates clustering.
- **Load Factor Constraint:** Must maintain $ \alpha < 0.75 $. When $ \alpha \ge 0.75 $, the table must be dynamically **rehashed** to a new prime capacity.
