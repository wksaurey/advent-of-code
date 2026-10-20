# aoc retro

## 2026-10-20 — repo skeleton, util move, clangd

- [decision] Context: per-year aoc repos duplicated utils and tracked inputs. Decision: one repo `aoc/`, split by language then year (`cpp/<YEAR>/dayNN.cpp`, shared `cpp/util/`), inputs gitignored and downloaded per machine. Rationale: one shared util per language that he grows by hand; AoC asks inputs not be shared. Caveats: old years still live in `aoc_bak/` unmigrated.
- [lesson] Remote must be `git@github-personal:wksaurey/advent-of-code.git`; plain `git@github.com` authenticates as the work account.
- [lesson] clangd reads `cpp/compile_flags.txt` (`-xc++`, `-I.`, `-std=c++20`), never the Makefile. Keep the two flag sets in sync.
- [lesson] util headers renamed `str_util` / `math_util` so they cannot shadow `<string.h>` / `<math.h>`; `io` kept.
