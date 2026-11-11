# C++ practice

Small console programs I wrote while learning C++.

| File | What it does |
| --- | --- |
| `calculator.cpp` | Calculator for expressions like `7 * 6`, with a check for division by zero |
| `tic_tac_toe.cpp` | Tic-tac-toe for two players in the console |
| `fire.cpp` | Animated coloured fire in the terminal, with settings for wind, cooling and colours |
| `word_counter.cpp` | Counts lines, words and characters in a text file and shows the most frequent words |

## How to run

You need a C++ compiler, for example g++ (MinGW on Windows).

```
g++ calculator.cpp -o calculator
./calculator
```

```
g++ tic_tac_toe.cpp -o tic_tac_toe
./tic_tac_toe
```

```
g++ word_counter.cpp -o word_counter
./word_counter README.md 5
```

```
g++ fire.cpp -o fire
./fire
```

## What I practised

- functions, loops and `switch`
- two-dimensional arrays
- reading files with `ifstream`
- simple simulation and terminal colour codes (`fire.cpp`)
- `std::map`, `std::vector` and sorting
