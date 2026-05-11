# Hash Table – Linear Probing (C++)

A hash table implementation using open addressing with linear probing.  
Uses a dummy-item technique to mark deleted slots without breaking probe chains.

## Operations
- Insert (with collision resolution)
- Search
- Delete
- Display (table structure)

## Compile & Run
```bash
g++ -std=c++17 hash-table.cpp -o hash-table
./hash-table
