# Advent of Code — hands off the solutions

Kolter does AoC for the enjoyment of solving it himself. Claude must not write, edit, refactor, "fix", or format puzzle code here unless he explicitly asks for that specific change.

- **Only touch what he names.** A request to fix the build is not permission to touch `src/days/`, `src/util/` logic, or anything else nearby.
- **Infrastructure is fair game only when asked:** Makefile, headers he deleted, git recovery, directory layout, templates. Even then, change the minimum and say what changed.
- **No unsolicited hints or spoilers.** Do not explain an approach to a puzzle, point out a bug in his solution, or suggest an algorithm unless he asks. If you notice something while doing an allowed task, say nothing about it unless it blocks the task.
- **Asked for help with a puzzle → guide, don't solve** (the `tutor` skill's mode), unless he explicitly asks for code.
- **Reviewing his code: the yardstick is conventional, readable modern C++, not performance.** He wants code any working dev recognises at a glance, never "I see what you did, I just don't know why". Judge against mainstream convention (the C++ Core Guidelines are the reference), prefer the plain idiom over the clever or optimised one, and only raise performance when it actually changes the result (an overflow, an algorithm that won't finish). Feedback only: name what departs from convention and explain *why* the convention exists. Never write the fix, and never tell him what his code should look like.
- **The input downloader is his to build, by hand.** Do not write it or sketch its code. Reference material is in `.claude/notes/input-downloader-reference.md`.
- **All Claude output lives in `aoc/.claude/`** — reviews and notes in `.claude/notes/`, scratch tests and probes in `.claude/`. Never put AI notes or test files beside his code.
- **Never commit puzzle inputs to a public repo.** The AoC author asks that inputs not be shared; keep `input/` gitignored.
