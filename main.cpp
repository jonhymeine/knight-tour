#include <iostream>
#include <iomanip>
#include <utility>
#include <stack>
#include <chrono>
#include <vector>
#include <cstdlib>

using namespace std;

int BOARD_SIZE = 8;

enum Direction
{
  UNVISITED,
  VISITED,
  UP_RIGHT,
  RIGHT_UP,
  RIGHT_DOWN,
  DOWN_RIGHT,
  DOWN_LEFT,
  LEFT_DOWN,
  LEFT_UP,
  UP_LEFT,
};

void printMatrix(const vector<vector<int>> &matrix)
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      cout << setw(2) << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

bool goToNextPosition(pair<int, int> &current_position, vector<vector<Direction>> &visited_squares, Direction ignored_direction = UNVISITED)
{
  auto [row, col] = current_position;

  if (row - 2 >= 0 && col + 1 < BOARD_SIZE && visited_squares[row - 2][col + 1] == UNVISITED && ignored_direction < UP_RIGHT)
  {
    current_position = make_pair(row - 2, col + 1);
    visited_squares[row][col] = UP_RIGHT;
    return true;
  }
  else if (row - 1 >= 0 && col + 2 < BOARD_SIZE && visited_squares[row - 1][col + 2] == UNVISITED && ignored_direction < RIGHT_UP)
  {
    current_position = make_pair(row - 1, col + 2);
    visited_squares[row][col] = RIGHT_UP;
    return true;
  }
  else if (row + 1 < BOARD_SIZE && col + 2 < BOARD_SIZE && visited_squares[row + 1][col + 2] == UNVISITED && ignored_direction < RIGHT_DOWN)
  {
    current_position = make_pair(row + 1, col + 2);
    visited_squares[row][col] = RIGHT_DOWN;
    return true;
  }
  else if (row + 2 < BOARD_SIZE && col + 1 < BOARD_SIZE && visited_squares[row + 2][col + 1] == UNVISITED && ignored_direction < DOWN_RIGHT)
  {
    current_position = make_pair(row + 2, col + 1);
    visited_squares[row][col] = DOWN_RIGHT;
    return true;
  }
  else if (row + 2 < BOARD_SIZE && col - 1 >= 0 && visited_squares[row + 2][col - 1] == UNVISITED && ignored_direction < DOWN_LEFT)
  {
    current_position = make_pair(row + 2, col - 1);
    visited_squares[row][col] = DOWN_LEFT;
    return true;
  }
  else if (row + 1 < BOARD_SIZE && col - 2 >= 0 && visited_squares[row + 1][col - 2] == UNVISITED && ignored_direction < LEFT_DOWN)
  {
    current_position = make_pair(row + 1, col - 2);
    visited_squares[row][col] = LEFT_DOWN;
    return true;
  }
  else if (row - 1 >= 0 && col - 2 >= 0 && visited_squares[row - 1][col - 2] == UNVISITED && ignored_direction < LEFT_UP)
  {
    current_position = make_pair(row - 1, col - 2);
    visited_squares[row][col] = LEFT_UP;
    return true;
  }
  else if (row - 2 >= 0 && col - 1 >= 0 && visited_squares[row - 2][col - 1] == UNVISITED && ignored_direction < UP_LEFT)
  {
    current_position = make_pair(row - 2, col - 1);
    visited_squares[row][col] = UP_LEFT;
    return true;
  }

  return false;
}

bool isReachable(pair<int, int> from, pair<int, int> to)
{
  auto [from_row, from_col] = from;
  auto [to_row, to_col] = to;

  return (abs(from_row - to_row) == 2 && abs(from_col - to_col) == 1) ||
         (abs(from_row - to_row) == 1 && abs(from_col - to_col) == 2);
}

int main(int argc, char *argv[])
{
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
  int unvisited_squares_count = BOARD_SIZE * BOARD_SIZE;
  vector<vector<Direction>> visited_squares(BOARD_SIZE, vector<Direction>(BOARD_SIZE, UNVISITED));
  Direction ignored_direction = UNVISITED;
  stack<pair<int, int>> move_history;
  int backtracks = 0;

  vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
  int step = 1;

  auto start_time = chrono::high_resolution_clock::now();

  while (unvisited_squares_count > 0)
  {
    // Mark current position as visited if not already
    if (visited_squares[knight_position.first][knight_position.second] == UNVISITED)
    {
      visited_squares[knight_position.first][knight_position.second] = VISITED;
      board[knight_position.first][knight_position.second] = step++;
      move_history.push(knight_position);
      unvisited_squares_count--;
      cout << "Knight is at position: (" << knight_position.first << ", " << knight_position.second << ")\n";
    }

    if (unvisited_squares_count == 0)
      break;

    bool moved = goToNextPosition(knight_position, visited_squares, ignored_direction);

    if (moved)
    {
      ignored_direction = UNVISITED;
    }
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
      move_history.pop();
      unvisited_squares_count++;

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
  {
    cout << "A closed knight's tour was found!\n";
  }
  else
  {
    cout << "An open knight's tour was found.\n";
  }

  cout << "Time spent: " << duration.count() << " ms\n";
  cout << "Number of backtracks: " << backtracks << "\n";

  printMatrix(board);
  return 0;
}