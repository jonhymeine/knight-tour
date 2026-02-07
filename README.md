# knight-tour

## 🔧 Build

Compile with g++ (requires C++17). The project now has two source files, so include both when compiling:

```bash
g++ -std=c++17 -O2 main.cpp knight_tour.cpp -o knight_tour
```

Or compile separately and link:

```bash
g++ -std=c++17 -O2 -c knight_tour.cpp
g++ -std=c++17 -O2 -c main.cpp
g++ knight_tour.o main.o -o knight_tour
```

If you use the **C/C++: g++ build active file** task in VS Code, make sure it builds both sources or adapt it to run the command above.

---

## ▶️ Run

Usage:

```bash
./knight_tour <board_size> [--brute-force]
```

Examples (8×8 board):

```bash
# Use heuristic (default)
./knight_tour 8

# Disable heuristic and use brute-force (slower)
./knight_tour 8 --brute-force
```

Notes:

- The program requires a board size of **at least 5**.
- After running, the program prompts:

```
Enter the knight's position (row and column):
```

Enter two integers (0-based indices), e.g., `0 0`.

- **Heuristic behavior:** By default the program uses heuristic (it prefers moves that lead to squares with fewer onward moves), which greatly reduces backtracking and runtime for typical boards.
- **Brute-force mode:** Pass `--brute-force` to disable the heuristic and force the program to use the deterministic move order (this may take much longer for larger boards).

---

## 📋 Output

- The program prints each visited position as it runs.
- When finished it reports:
  - Whether the tour is **closed** or **open**
  - **Time spent** (milliseconds)
  - **Number of backtracks**
- The final board (step numbers) is printed showing the order of moves.

---

## ℹ️ Implementation notes

- The heuristic uses a precomputed `possible_moves_board` and an `updatePossibleMoves` helper to avoid recounting onward moves on every decision, which improves performance.
- The code is split into:
  - `main.cpp` (program flow and CLI)
  - `knight_tour.cpp / knight_tour.h` (core logic and helpers)

---

## 💡 Tips

- Try corners (e.g., `0 0`) and center positions to see different behaviors.
- For experimentation, compare the number of backtracks with and without `--brute-force` to see the effect of the heuristic.
