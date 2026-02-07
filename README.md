# knight-tour

## 🔧 Build

Compile with g++ (requires C++17):

```bash
g++ -std=c++17 -O2 main.cpp -o knight_tour
```

Alternatively, use the provided VS Code task **C/C++: g++ build active file**.

---

## ▶️ Run

Usage:

```bash
./knight_tour <board_size>
```

Example (8×8 board):

```bash
./knight_tour 8
```

Notes:

- The program requires a board size of **at least 5**.
- After running, the program prompts:

```
Enter the knight's position (row and column):
```

Enter two integers (0-based indices), e.g., `0 0`.

---

## 📋 Output

- The program prints each visited position as it runs.
- When finished it reports:
  - Whether the tour is **closed** or **open**
  - **Time spent** (milliseconds)
  - **Number of backtracks**
- The final board (step numbers) is printed showing the order of moves.

---

## ℹ️ Requirements

- g++ with C++17 support
- No external libraries required

---

## 💡 Tips

- Try different board sizes, e.g., `5`, `6`, `8`, `10`.
- Larger boards may take much longer (brute-force search), so expect runtime to increase rapidly.
