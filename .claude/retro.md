# aoc retro

## 2026-10-20 — repo skeleton, util move, clangd

- [decision] Context: per-year aoc repos duplicated utils and tracked inputs. Decision: one repo `aoc/`, split by language then year (`cpp/<YEAR>/dayNN.cpp`, shared `cpp/util/`), inputs gitignored and downloaded per machine. Rationale: one shared util per language that he grows by hand; AoC asks inputs not be shared. Caveats: old years still live in `aoc_bak/` unmigrated.
- [lesson] Remote must be `git@github-personal:wksaurey/advent-of-code.git`; plain `git@github.com` authenticates as the work account.
- [lesson] clangd reads `cpp/compile_flags.txt` (`-xc++`, `-I.`, `-std=c++20`), never the Makefile. Keep the two flag sets in sync.
- [lesson] util headers renamed `str_util` / `math_util` so they cannot shadow `<string.h>` / `<math.h>`; `io` kept.

## 2026-10-21 — Makefile year arg, input path via argv, nested-repo cleanup
- [retro] `cpp/Makefile`: `make dayNN 2025` now selects the year (`YEAR_ARG` from `$(MAKECMDGOALS)` with a `.PHONY` no-op rule; `.PHONY` is required because `cpp/2025/` is a real directory). Year defaults to 2026; `YEAR=` still overrides.
- [decision] Context: input paths were hardcoded per puzzle and the run rule's `cd ..` assumed `aoc/` as cwd. Decision (Kolter's, he wrote it): inputs live in `aoc/input/<YEAR>/` (shared across languages), the run rule passes `input/$(YEAR)/day$*.txt` as `argv[1]`, and each solution reads `argv[1]` with an `argc < 2` guard. Rationale: keeps paths out of puzzle code so a year can be done in several languages. Caveats: only day01 2025 converted so far; other days still hardcode a path.
- [lesson] A relative path resolves against the process cwd that the recipe's `cd` sets, never against the binary's folder. That was the one confusion; a folder tree with "make starts here / cd lands here" resolved it.
- [lesson] `cpp/2025` was once its own repo; `git add -A` staged it as a gitlink (mode 160000), and deleting its `.git` left the gitlink in the index. Fix was `git restore --staged cpp/2025 && git add cpp/2025` from `aoc/` (it had never been committed). `git check-ignore` refuses to look inside a path the index thinks is a submodule, so verify ignores only after the gitlink is gone.
- [retro] NEXT: a `TEST=1` switch so the run rule passes `day$*_test.txt` (Kolter's pick for next session; he will write it, following the `DEBUG` pattern). Not committed at session end: Makefile change, `cpp/2025/*.cpp`.
