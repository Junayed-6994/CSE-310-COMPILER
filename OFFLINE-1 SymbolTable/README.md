# Symbol Table Implementation (Offline 1)

## Overview

This project implements a **Symbol Table** using hashing with chaining, as part of a compiler design assignment. It supports symbol management along with nested scope handling.

---

## Data Structures Used

* **Hash Table** – for efficient symbol storage and lookup
* **Linked List (Chaining)** – for collision resolution
* **Scope Table (Stack-like structure)** – for managing nested scopes

---

## Features

* Insert, lookup, and delete symbols
* Collision handling using chaining
* Multiple scope support (enter/exit scope)
* Print current and all scope tables

---

## How to Build & Run

```bash
chmod +x 2205132_build.sh
./2205132_build.sh
```

---

## Input Commands

```
I <name> <type>   # Insert
L <name>          # Lookup
D <name>          # Delete
P A               # Print all scopes
P C               # Print current scope
S                 # Enter scope
E                 # Exit scope
```

---

## Files

* `main.cpp` – main driver code
* `SymbolInfo.*` – symbol structure
* `ScopeTable.*` – scope handling
* `2205132_build.sh` – build script

---
