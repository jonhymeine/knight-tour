#ifndef KNIGHT_TOUR_H
#define KNIGHT_TOUR_H

#include <vector>
#include <utility>

extern int BOARD_SIZE;

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

/**
 * @brief Prints the board matrix
 * @param matrix The board matrix to print
 */
void printBoard(const std::vector<std::vector<int>> &matrix);

/**
 * @brief Attempts to move the knight to the next valid position
 * @param current_position The current position of the knight (will be updated if move is successful)
 * @param visited_squares Matrix tracking visited squares and their exit directions
 * @param ignored_direction Direction to ignore (for backtracking)
 * @return true if a valid move was found, false otherwise
 */
bool goToNextPosition(std::pair<int, int> &current_position,
                      std::vector<std::vector<Direction>> &visited_squares,
                      Direction ignored_direction = UNVISITED);

/**
 * @brief Checks if two positions are reachable by a knight's move
 * @param from Starting position
 * @param to Target position
 * @return true if positions are reachable by a valid knight move
 */
bool isReachable(std::pair<int, int> from, std::pair<int, int> to);

#endif // KNIGHT_TOUR_H
