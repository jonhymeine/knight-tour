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
 * @brief Attempts to move the knight preferring positions with fewer onward moves
 * @param current_position The current position of the knight (will be updated if move is successful)
 * @param visited_squares Matrix tracking visited squares and their exit directions
 * @param possible_moves_board Pre-computed board with the count of possible moves for each square
 * @param ignored_direction Direction to ignore (for backtracking)
 * @return true if a valid move was found, false otherwise
 */
bool goToNextPositionHeuristic(std::pair<int, int> &current_position,
                               std::vector<std::vector<Direction>> &visited_squares,
                               const std::vector<std::vector<int>> &possible_moves_board,
                               Direction ignored_direction = UNVISITED);

/**
 * @brief Updates the possible moves count for neighbors of a given square
 * @param possible_moves_board The board to update
 * @param row Row of the square being visited/unvisited
 * @param col Column of the square being visited/unvisited
 * @param delta -1 when visiting (decrement neighbors), +1 when backtracking (increment neighbors)
 */
void updatePossibleMoves(std::vector<std::vector<int>> &possible_moves_board, int row, int col, int delta);

/**
 * @brief Checks if two positions are reachable by a knight's move
 * @param from Starting position
 * @param to Target position
 * @return true if positions are reachable by a valid knight move
 */
bool isReachable(std::pair<int, int> from, std::pair<int, int> to);

/**
 * @brief Maps the number of possible moves from each square on the board
 * @param possible_moves_board Matrix to be filled with the count of possible moves from each square
 */
void mapPossibleMoves(std::vector<std::vector<int>> &possible_moves_board);

#endif // KNIGHT_TOUR_H
