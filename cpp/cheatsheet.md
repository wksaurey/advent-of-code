# C++ cheat sheet

The C++ that comes up in AoC: headers and the build, values / references / pointers, strings, containers and I/O. `T` = any type (`int`, `std::string`, ...). `x`, `v`, `s` = any variable.

**Patterns that cover most of the list:**
- **`&` and `*` mean two things.** In a **type** (`int& r`, `int* p`) they declare a reference / pointer. In an **expression** (`&x`, `*p`) they mean *address of* / *thing pointed at*.
- **Read declarations right to left:** `const std::string& s` = "s is a reference to a string that is const".
- **`const` = read-only.** `const T&` is the default way to pass anything bigger than a number when you only read it.
- **`std::`** = lives in the standard library. Write it out; never put `using namespace std;` in a header.
- **`<...>` vs `"..."`** in `#include`: angle brackets search the system headers, quotes search next to the file and the `-I` folders first.

## Headers and the build

| Thing | Example | Does | Remember it |
|---|---|---|---|
| header | `util/io.h` | **declares** functions (name, return type, params, no body) | the promise: "this exists, call it like this" |
| source | `util/io.cpp` | **defines** them (the body) | the work. Includes its own header first |
| include guard | `#ifndef UTIL_IO_H` / `#define UTIL_IO_H` / `#endif` | skips the header if it was already pasted in | name it after the path: `util/io.h` -> `UTIL_IO_H` |
| `#include` | `#include "util/io.h"` | pastes the file's text in, before compiling | **preprocessor**: any line starting with `#` |
| declaration | `int f(int x);` | says `f` exists | ends in `;` |
| definition | `int f(int x) { ... }` | the body | ends in `}`. Exactly one per program |
| compile | `g++ -c day01.cpp` | `.cpp` -> `.o` (object file) | one `.o` per `.cpp` |
| link | `g++ day01.o io.o -o day01` | `.o` files -> program | where a declared-but-never-defined function finally errors |

Build steps: **preprocess** (paste includes) -> **compile** (each `.cpp` alone) -> **link** (join the `.o` files). `compile_flags.txt` tells clangd (the editor) the same flags the Makefile gives g++.

## Value, address, pointer, reference

| Term | Example | Is | Remember it |
|---|---|---|---|
| value | `int a = 5;` | the data itself | your own copy |
| address | `&a` | where `a` lives in memory | `&` in an expression = "address of" |
| pointer | `int* p = &a;` | a variable **holding an address** | its own box, with its own address |
| dereference | `*p = 9;` | the thing `p` points at | `*` in an expression = "go there" |
| reference | `int& r = a;` | **another name** for `a` | no new box. `r = 7` sets `a` |
| null pointer | `int* p = nullptr;` | points at nothing | references can never be null |
| arrow | `p->size()` | `(*p).size()` | member through a pointer |

```
int a = 5;
int* p = &a;
int& r = a;

   address 0x100            address 0x200
  ┌────────────┐           ┌────────────┐
  │     5      │ ◄──────── │   0x100    │
  └────────────┘           └────────────┘
   names: a, r              name: p
```

Reference vs pointer: a reference must be bound when created and can never be pointed elsewhere; a pointer can be `nullptr` and can be changed to point somewhere new. Use a reference when the thing must exist, a pointer when "nothing" is a valid answer.

## Function parameters

| Parameter | Function gets | Use when |
|---|---|---|
| `int x` | a copy | small types: `int`, `char`, `double`, `bool` |
| `const std::string& s` | the caller's string, read-only, no copy | big things you only **read**. The common case |
| `std::string& s` | the caller's string, can change it | changing the argument is the point |
| `std::string* s` | an address, maybe `nullptr` | "nothing" is allowed. Rare in modern C++ |
| `T arr[]` | secretly `T* arr` | **array decay**: the size is lost |

Return results by value (`std::vector<std::string> readLines(...)`). It's cheap: the compiler builds it straight into the caller's variable (**copy elision**) or **moves** it.

## Loops

| Form | Each `x` is | Remember it |
|---|---|---|
| `for (int i = 0; i < n; i++)` | an index | classic. Use `std::size_t` (or cast) when comparing to `.size()` |
| `for (auto x : v)` | a **copy** | changing `x` does nothing to `v` |
| `for (auto& x : v)` | a **reference** | changing `x` changes `v` |
| `for (const auto& x : v)` | a read-only reference | no copy, no changes. The default |
| `while (cond)` / `do { } while (cond);` | - | `do` runs at least once |

`auto` = "compiler, work out the type". `auto&` / `const auto&` add the reference on top.

## Strings (`#include <string>`)

| Expression | Does | Remember it |
|---|---|---|
| `s.size()` / `s.length()` | number of chars | same thing |
| `s.empty()` | true if `""` | |
| `s[i]` | char at i | no bounds check. `s.at(i)` checks and throws |
| `s.substr(pos, len)` | copy of part of s | **pos, length**, not start, end. Leave off `len` for "to the end" |
| `s.find("x")` | index of first match | not found = `std::string::npos` |
| `s + t`, `s += t` | join | |
| `std::stoi(s)` / `std::stoll(s)` | string -> int / long long | throws if `s` doesn't start with a number |
| `std::to_string(n)` | number -> string | |
| `s.back()` / `s.pop_back()` | last char / remove it | |

`'a'` (single quotes) is a `char`; `"a"` (double quotes) is a string. A `char` is a small number: `'7' - '0'` is `7`.

Splitting text: `std::istringstream` (`#include <sstream>`) wraps a string so you can read it like a stream: `stream >> n` reads the next whitespace-separated number, `std::getline(stream, token, ',')` reads up to the next comma.

## Containers

| Container | Include | Is | Common use |
|---|---|---|---|
| `std::vector<T>` | `<vector>` | growable array | `push_back(x)`, `v[i]`, `v.size()`, `v.back()` |
| `std::array<T, N>` | `<array>` | fixed-size array that knows its size | when N never changes |
| `std::map<K, V>` | `<map>` | key -> value, **sorted** by key | `m[key]`, `m.count(key)` |
| `std::unordered_map<K, V>` | `<unordered_map>` | key -> value, hashed, faster | same interface as `map`, no order |
| `std::set<T>` / `std::unordered_set<T>` | `<set>` / `<unordered_set>` | unique values | `insert(x)`, `count(x)` = "is it in?" |
| `std::pair<A, B>` | `<utility>` | two values | `.first`, `.second` |
| `std::deque<T>` / `std::queue<T>` | `<deque>` / `<queue>` | double-ended queue / FIFO | BFS-style queues |
| `std::priority_queue<T>` | `<queue>` | always gives the **largest** next | `top()`, `push`, `pop` |

Handy from `<algorithm>`: `std::sort(v.begin(), v.end())`, `std::reverse(...)`, `std::min` / `std::max`, `std::count(...)`. From `<numeric>`: `std::accumulate(v.begin(), v.end(), 0)` sums.

`m[key]` **creates** the key (value 0 / empty) if it isn't there. To only check, use `m.count(key)` or `m.find(key)`.

## Output and input (`#include <iostream>`)

| Expression | Does | Remember it |
|---|---|---|
| `std::cout << x` | print to stdout | chain: `std::cout << a << " " << b` |
| `std::cerr << x` | print to stderr | for errors. Unbuffered |
| `"\n"` | newline | just the newline |
| `std::endl` | newline **and flush** | flushing every line in a loop is slow |
| `std::ifstream file(name)` | open a file (`<fstream>`) | closes itself at the end of scope (**RAII**) |
| `std::getline(file, line)` | read one line | `false` at end of file, so it can be a loop condition |

## Integer sizes

| Type | Holds about | Remember it |
|---|---|---|
| `int` | ±2.1 billion (32-bit) | overflows silently: AoC answers often outgrow it |
| `long long` | ±9.2 × 10^18 (64-bit) | the safe default for big answers |
| `std::size_t` | what `.size()` returns | **unsigned**: `0 - 1` wraps to a huge number |

Traps, one clause each:
- `int / int` is integer division: `7 / 2` is `3`. Make one side a `double` for `3.5`.
- `%` keeps the sign of the left side: `-7 % 3` is `-1`, not `2`.
- a variable declared without a value (`int x;`) holds garbage until assigned.
- `if (x = 5)` assigns; `if (x == 5)` compares. `-Wall` warns.
- returning a reference or pointer to a local variable leaves it **dangling** (the local is gone).
- `s[i]` / `v[i]` past the end is **undefined behaviour**, not an error: it may crash, corrupt something, or seem fine.
- comparing an `int` to `.size()` mixes signed and unsigned; `-Wextra` warns.
- a missing `return` in a non-`void` function compiles (with a warning) and returns garbage.
