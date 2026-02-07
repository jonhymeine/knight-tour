#include "knight_tour.h"

#include <iostream>
#include <iomanip>
#include <utility>
#include <cstdlib>

void printBoard(const std::vector<std::vector<int>> &matrix)
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      std::cout << std::setw(2) << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool goToNextPosition(std::pair<int, int> &current_position, std::vector<std::vector<Direction>> &visited_squares, Direction ignored_direction)
{
  auto [row, col] = current_position;

  if (row - 2 >= 0 && col + 1 < BOARD_SIZE && visited_squares[row - 2][col + 1] == UNVISITED && ignored_direction < UP_RIGHT)
  {
    current_position = std::make_pair(row - 2, col + 1);
    visited_squares[row][col] = UP_RIGHT;
    return true;
  }
  if (row - 1 >= 0 && col + 2 < BOARD_SIZE && visited_squares[row - 1][col + 2] == UNVISITED && ignored_direction < RIGHT_UP)
  {
    current_position = std::make_pair(row - 1, col + 2);
    visited_squares[row][col] = RIGHT_UP;
    return true;
  }
  if (row + 1 < BOARD_SIZE && col + 2 < BOARD_SIZE && visited_squares[row + 1][col + 2] == UNVISITED && ignored_direction < RIGHT_DOWN)
  {
    current_position = std::make_pair(row + 1, col + 2);
    visited_squares[row][col] = RIGHT_DOWN;
    return true;
  }
  if (row + 2 < BOARD_SIZE && col + 1 < BOARD_SIZE && visited_squares[row + 2][col + 1] == UNVISITED && ignored_direction < DOWN_RIGHT)
  {
    current_position = std::make_pair(row + 2, col + 1);
    visited_squares[row][col] = DOWN_RIGHT;
    return true;
  }
  if (row + 2 < BOARD_SIZE && col - 1 >= 0 && visited_squares[row + 2][col - 1] == UNVISITED && ignored_direction < DOWN_LEFT)
  {
    current_position = std::make_pair(row + 2, col - 1);
    visited_squares[row][col] = DOWN_LEFT;
    return true;
  }
  if (row + 1 < BOARD_SIZE && col - 2 >= 0 && visited_squares[row + 1][col - 2] == UNVISITED && ignored_direction < LEFT_DOWN)
  {
    current_position = std::make_pair(row + 1, col - 2);
    visited_squares[row][col] = LEFT_DOWN;
    return true;
  }
  if (row - 1 >= 0 && col - 2 >= 0 && visited_squares[row - 1][col - 2] == UNVISITED && ignored_direction < LEFT_UP)
  {
    current_position = std::make_pair(row - 1, col - 2);
    visited_squares[row][col] = LEFT_UP;
    return true;
  }
  if (row - 2 >= 0 && col - 1 >= 0 && visited_squares[row - 2][col - 1] == UNVISITED && ignored_direction < UP_LEFT)
  {
    current_position = std::make_pair(row - 2, col - 1);
    visited_squares[row][col] = UP_LEFT;
    return true;
  }

  return false;
}

bool goToNextPositionHeuristic(std::pair<int, int> &current_position, std::vector<std::vector<Direction>> &visited_squares, const std::vector<std::vector<int>> &possible_moves_board, Direction ignored_direction)
{
  auto [row, col] = current_position;

  const int delta_row[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
  const int delta_col[8] = {1, 2, 2, 1, -1, -2, -2, -1};
  const Direction dirs[8] = {UP_RIGHT, RIGHT_UP, RIGHT_DOWN, DOWN_RIGHT, DOWN_LEFT, LEFT_DOWN, LEFT_UP, UP_LEFT};

  int best_row = -1, best_col = -1;
  Direction best_dir = UNVISITED;
  int best_score = 9; // more than max possible (8)

  for (int k = 0; k < 8; ++k)
  {
    if (dirs[k] <= ignored_direction)
      continue;

    int new_row = row + delta_row[k];
    int new_col = col + delta_col[k];

    // Check bounds and if unvisited
    if (new_row < 0 || new_row >= BOARD_SIZE || new_col < 0 || new_col >= BOARD_SIZE)
      continue;
    if (visited_squares[new_row][new_col] != UNVISITED)
      continue;

    int score = possible_moves_board[new_row][new_col];

    if (score < best_score)
    {
      best_score = score;
      best_row = new_row;
      best_col = new_col;
      best_dir = dirs[k];
    }
  }

  if (best_row == -1)
    return false;

  current_position = std::make_pair(best_row, best_col);
  visited_squares[row][col] = best_dir;
  return true;
}

void updatePossibleMoves(std::vector<std::vector<int>> &possible_moves_board, int row, int col, int delta)
{
  const int delta_row[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
  const int delta_col[8] = {1, 2, 2, 1, -1, -2, -2, -1};

  for (int k = 0; k < 8; ++k)
  {
    int new_row = row + delta_row[k];
    int new_col = col + delta_col[k];
    if (new_row >= 0 && new_row < BOARD_SIZE && new_col >= 0 && new_col < BOARD_SIZE)
      possible_moves_board[new_row][new_col] += delta;
  }
}

bool isReachable(std::pair<int, int> from, std::pair<int, int> to)
{
  auto [from_row, from_col] = from;
  auto [to_row, to_col] = to;

  return (std::abs(from_row - to_row) == 2 && std::abs(from_col - to_col) == 1) ||
         (std::abs(from_row - to_row) == 1 && std::abs(from_col - to_col) == 2);
}

void mapPossibleMoves(std::vector<std::vector<int>> &board)
{
  const int delta_row[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
  const int delta_col[8] = {1, 2, 2, 1, -1, -2, -2, -1};

  for (int row = 0; row < BOARD_SIZE; ++row)
  {
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
      int cnt = 0;
      for (int k = 0; k < 8; ++k)
      {
        int new_row = row + delta_row[k];
        int new_col = col + delta_col[k];
        if (new_row >= 0 && new_row < BOARD_SIZE && new_col >= 0 && new_col < BOARD_SIZE)
          ++cnt;
      }
      board[row][col] = cnt;
    }
  }
}
