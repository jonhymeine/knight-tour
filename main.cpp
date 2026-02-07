#include <iostream>
#include <iomanip>
#include <utility>
#include <stack>
#include <chrono>
#include <vector>
#include <cstdlib>

#include "knight_tour.h"

using namespace std;

int BOARD_SIZE = 8;

int main(int argc, char *argv[])
{
  bool brute_force_mode = false;

  if (argc < 2)
  {
    cout << "Usage: " << argv[0] << " <board_size>\n";
    return 1;
  }

  BOARD_SIZE = atoi(argv[1]);
  if (BOARD_SIZE < 5)
  {
    cout << "Board size must be at least 5.\n";
    return 1;
  }

  if (argc > 2 && string(argv[2]) == "--brute-force")
  {
    cout << "Brute-force mode enabled. This may take a long time for larger boards.\n";
    brute_force_mode = true;
  }

  pair<int, int> initial_position;

  cout << "Enter the knight's position (row and column):\n";
  cin >> initial_position.first >> initial_position.second;

  while (initial_position.first < 0 || initial_position.first >= BOARD_SIZE ||
         initial_position.second < 0 || initial_position.second >= BOARD_SIZE)
  {
    cout << "Invalid position. Please enter values between 0 and " << BOARD_SIZE - 1 << " for both row and column:\n";
    cin >> initial_position.first >> initial_position.second;
  }

  pair<int, int> knight_position = initial_position;
  const int max_steps = BOARD_SIZE * BOARD_SIZE;
  vector<vector<Direction>> visited_squares(BOARD_SIZE, vector<Direction>(BOARD_SIZE, UNVISITED));
  Direction ignored_direction = UNVISITED;
  stack<pair<int, int>> move_history;
  int backtracks = 0;

  vector<vector<int>> possible_moves_board(BOARD_SIZE, vector<int>(BOARD_SIZE));

  if (!brute_force_mode)
    mapPossibleMoves(possible_moves_board);

  vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
  int step = 1;

  auto start_time = chrono::high_resolution_clock::now();

  while (step <= max_steps)
  {
    // Mark current position as visited if not already
    if (visited_squares[knight_position.first][knight_position.second] == UNVISITED)
    {
      visited_squares[knight_position.first][knight_position.second] = VISITED;
      board[knight_position.first][knight_position.second] = step++;
      move_history.push(knight_position);

      if (!brute_force_mode)
        updatePossibleMoves(possible_moves_board, knight_position.first, knight_position.second, -1);

      cout << "Knight is at position: (" << knight_position.first << ", " << knight_position.second << ")\n";
    }

    if (step == max_steps + 1)
      break;

    bool moved = brute_force_mode
                     ? goToNextPosition(knight_position, visited_squares, ignored_direction)
                     : goToNextPositionHeuristic(knight_position, visited_squares, possible_moves_board, ignored_direction);

    if (moved)
      ignored_direction = UNVISITED;
    else
    {
      backtracks++;
      if (move_history.empty())
      {
        cout << "No more moves available and no history to backtrack. Ending the tour.\n";
        break;
      }

      // Backtrack: unmark current position and go back
      pair<int, int> current = move_history.top();
      visited_squares[current.first][current.second] = UNVISITED;
      board[current.first][current.second] = 0;
      step--;

      if (!brute_force_mode)
        updatePossibleMoves(possible_moves_board, current.first, current.second, 1);

      move_history.pop();

      if (move_history.empty())
      {
        cout << "No more moves available and no history to backtrack. Ending the tour.\n";
        break;
      }

      knight_position = move_history.top();
      ignored_direction = visited_squares[knight_position.first][knight_position.second];
      cout << "Backtracking to position: (" << knight_position.first << ", " << knight_position.second << ")\n";
    }
  }

  auto end_time = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

  if (isReachable(knight_position, initial_position))
    cout << "A closed knight's tour was found!\n";
  else
    cout << "An open knight's tour was found.\n";

  cout << "Time spent: " << duration.count() << " ms\n";
  cout << "Number of backtracks: " << backtracks << "\n";

  printBoard(board);
  return 0;
}