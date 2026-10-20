# Input downloader — reference

Kolter is building his own AoC input downloader, by hand, without AI writing it. This note records a reference implementation he flagged on 2026-10-20 and what it does. It is reference material, not a spec.

**Source:** https://github.com/jonathanpaulson/AdventOfCode/blob/master/get_input.py (Jonathan Paulson, a long-time top AoC competitor)

## What it does

- Takes `--year` and `--day` (argparse), fetches `https://adventofcode.com/<year>/day/<day>/input`.
- Authenticates with the `session` cookie from a logged-in browser (DevTools > Application > Cookies > adventofcode.com > `session`).
- Sends a **User-Agent** naming the script and a contact email. AoC's creator asks automated tools to do this, so he can reach the owner of a misbehaving tool.
- Prints the input to stdout (usage: `./get_input.py > 1.in`) and the first 10 lines to stderr, so you see a preview while the file is written.
- Header comment: "DO NOT run this in a loop, just once."

## Notes on it, as found

- The session cookie is a hardcoded string in the script. This repo gitignores `.env` for exactly that cookie.
- It imports `requests` but never uses it; the fetch runs `curl` through `subprocess` with `shell=True`.
- No caching: it re-downloads every time it is run. AoC asks tools to cache inputs and not re-request one they already have.

## AoC's asks for automated tools (from its FAQ / creator)

- Cache inputs locally; don't re-download.
- Throttle: don't hammer the server, and never request a puzzle before it unlocks.
- Set a User-Agent identifying the tool and a contact.
- Keep the session cookie secret; it is a login.
