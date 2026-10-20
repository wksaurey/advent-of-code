# AoC C++ style review — 2026-10-20

Scope: `aoc/cpp/util/{io,str_util,math_util}`, `aoc_bak/aoc25/src/days/{day01,day02,dayxx}.cpp`. Formatting, syntax and C++ habits only. No solution logic was assessed, and nothing here is a rewrite. Each item says what is there and why the convention exists, so the call is yours.

Overall: the code is readable and mostly consistent. `io.h` is the best-formed file (guard, includes, const-ref parameter, returns a value). Most of what follows is the newer `str_util.cpp` drifting from conventions the older files already follow.

## Your conventions, as the code shows them

- Functions `camelCase` (`readLines`, `splitString`), variables `snake_case` (`reset_count`). Consistent across every file.
- 4-space indent, brace on the same line, space after keywords: `if (`, `while (`, `for (`.
- `std::` written out explicitly in `io.cpp` and every day file.
- Header guards named `UTIL_<NAME>_H` with a `// UTIL_<NAME>_H` comment on the `#endif`.

## Where the code departs from them

### The `using namespace std` split
`str_util.cpp` has `using namespace std;`; every other file writes `std::`. Why people avoid it: it pulls hundreds of names (`count`, `distance`, `size`, `data`...) into scope, so one of your own names can silently collide with a standard one. In a `.cpp` the damage stays in that file, which is why it is tolerated there; in a header it leaks into every file that includes it, which is why it is banned there. Either choice is defensible in a `.cpp`; mixing them is the thing to notice.

### The `while(` spacing
`str_util.cpp` has `while(getline...`; everywhere else is `while (`. Pure consistency. A formatter (`clang-format`) would enforce this for you if you ever want that.

### The leading blank line
`str_util.cpp` starts with an empty line before its first `#include`. Harmless, just inconsistent with the others.

### Missing newline at end of file
`day01.cpp`, `day02.cpp` and `dayxx.cpp` end on `}` with no final newline, so the template passes it on to every new day. Why it matters: POSIX defines a text line as ending in a newline, so tools like `cat`, `diff` and `git` treat the last line as incomplete (`\ No newline at end of file` in diffs). Most editors have a "insert final newline" setting.

### Trailing whitespace on blank lines
`io.cpp`'s two blank lines inside `readLines` contain four spaces each. Invisible, but shows up as noise in diffs. Editors can strip it on save.

### Empty headers have no include guard
`str_util.h` and `math_util.h` are empty, so they have no guard yet, and `splitString` has no declaration anywhere. A day file cannot call it until the header declares it. When you fill them in, `io.h` is your own template.

## C++ habits worth relearning the "why" of

### Include order: own header first in a `.cpp`
`io.cpp` and `str_util.cpp` include their own header first; the day files include `<iostream>` first. The own-header-first rule is about a module's own `.cpp`: if `io.h` forgot to include `<vector>`, putting it first makes `io.cpp` fail to compile, so the header's missing include is caught immediately rather than hidden by something included earlier. For a day file with no header of its own, order is taste.

### Include what you use
The day files use `std::string` but never include `<string>`; it arrives transitively through `util/io.h`. It works today, and breaks the day `io.h` stops needing it. Conversely, `str_util.cpp` includes `<iostream>` and uses nothing from it.

### RAII and `file.close()`
`io.cpp` calls `file.close()` before returning. `std::ifstream` closes itself in its destructor when it goes out of scope; that is RAII (resource acquisition is initialisation), the idea that an object owns its resource and releases it automatically. The explicit call is not wrong, just redundant, and knowing why it is redundant is the useful part.

### `std::endl` versus `"\n"`
`day01.cpp` uses both. `std::endl` writes a newline **and** flushes the stream; `"\n"` only writes the newline. Flushing on every line inside a loop is the classic reason a C++ program prints slowly. `std::cerr` is unbuffered anyway, so `endl` there buys nothing.

### `splitString`'s parameter list
Three things in the signature, each with a reason:
- `string& input` is a non-const reference, but the function only reads it. A non-const reference tells the reader "this function may modify my argument" and also refuses temporaries and string literals as arguments. `readLines` already takes `const std::string&`, which is the read-only form.
- `string arr[]` decays to a pointer, so the function cannot know how big the caller's array is. If the input has more tokens than the array holds, it writes past the end: undefined behaviour, no error. This is the main reason modern C++ code reaches for `std::vector` or `std::array`.
- Results come back through an output array plus an `int& index` counter, while `readLines` returns its result by value. Two different styles in one small util library. Returning by value is cheap in modern C++ (move semantics / copy elision), which is why `readLines`' style is the common one now.

### The ambiguous error message
Every day file prints "Error opening the file or file is empty!". That hedge is forced by `readLines`: it returns an empty vector both when the file is missing and when it has no lines, so the caller cannot tell which happened. Worth knowing the hedge comes from the util's interface, not from the day file.

### Variable scope
`day01.cpp` declares `int distance_left;` near the top of `main`, uninitialised, and only uses it inside the loop. The usual guideline is to declare a variable at the narrowest scope where it is needed and initialise it on the same line, so it can never be read before it holds a value. (`-Wall` will warn on some uninitialised reads, but not all.)

### Repeated blocks
`day01.cpp` has two branches whose bodies are near-identical apart from one line. Not a style error, and the day is solved; just something you would likely notice yourself on a re-read.

### Debug output
`day01.cpp` prints on every iteration. The new Makefile's `DEBUG=1` adds `-DDEBUG`, which is a lever you set up for exactly this kind of output if you want it.

### Switching inputs by editing the filename
`day02.cpp` points at `day02_test.txt`; switching to the real input means editing source. Many AoC setups take the path from `argv` instead. Only worth it if the editing bothers you.
