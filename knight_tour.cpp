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

bool isReachable(std::pair<int, int> from, std::pair<int, int> to)
{
  auto [from_row, from_col] = from;
  auto [to_row, to_col] = to;

  return (std::abs(from_row - to_row) == 2 && std::abs(from_col - to_col) == 1) ||
         (std::abs(from_row - to_row) == 1 && std::abs(from_col - to_col) == 2);
}
