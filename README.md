# Binary Search Tree Spell Checker with Native Shuffling Backend

A high-performance spell checking application combining a custom C89 BST backend and a Python/Tkinter GUI, achieving $O(\log n)$ average lookup time.

## Highlights
- **Fisher-Yates Shuffling:** Randomizes sorted inputs in C89 prior to BST insertion to prevent linear degradation.
- **Strict Compliance:** Built with `-std=c89 -pedantic` and interfaced via Python `ctypes`.
- **Structure:** Core files include `src/tree.c`, `src/words.c`, `app.py`, and the `Makefile`.

## Installation & Execution
```bash
git clone https://github.com
cd SpellChek
make clean && make
python3 app.py
```

## Performance Benchmarks

Engine performance profiling metrics executed natively on a macOS subsystem environment:

- **Total Word Count Indexed:** 370,105 words
- **Tree Generation Delay:** ~434,511 microseconds (under 0.5 seconds)
- **Search Execution Profile:** 100,000 operational lookup loop cycles
- **Average Word Query Latency:** ~0.5 microseconds per unique search query


