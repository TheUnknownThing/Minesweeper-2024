#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <iostream>

/*
 * You may need to define some global variables for the information of the game map here.
 * Although we don't encourage to use global variables in real cpp projects, you may have to use them because the use of
 * class is not taught yet. However, if you are member of A-class or have learnt the use of cpp class, member functions,
 * etc., you're free to modify this structure.
 */
int rows;         // The count of rows of the game map. You MUST NOT modify its name.
int columns;      // The count of columns of the game map. You MUST NOT modify its name.
int total_mines;  // The count of mines of the game map. You MUST NOT modify its name. You should initialize this
                  // variable in function InitMap. It will be used in the advanced task.
int game_state;  // The state of the game, 0 for continuing, 1 for winning, -1 for losing. You MUST NOT modify its name.
int visit_count;        // The count of blocks visited.
int marked_mine_count;  // The count of mines marked.

int direction_x[8] = {0, 0, 1, -1, 1, -1, 1, -1};
int direction_y[8] = {1, -1, 0, 0, 1, -1, -1, 1};

int **initial_map;
int **visited_map;

/**
 * @brief The definition of function InitMap()
 *
 * @details This function is designed to read the initial map from stdin. For example, if there is a 3 * 3 map in which
 * mines are located at (0, 1) and (1, 2) (0-based), the stdin would be
 *     3 3
 *     .X.
 *     ...
 *     ..X
 * where X stands for a mine block and . stands for a normal block. After executing this function, your game map
 * would be initialized, with all the blocks unvisited.
 */

void InitMark(int x, int y) {
  for (int i = 0; i < 8; i++) {
    int next_r = x + direction_x[i];
    int next_c = y + direction_y[i];
    if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < columns && initial_map[next_r][next_c] != -1) {
      initial_map[next_r][next_c]++;
    }
  }
  return;
}

void InitMap() {
  std::cin >> rows >> columns;

  initial_map = new int *[rows];  // in the initial map, -1 for mine block, otherwise the number of mines around.
  visited_map = new int *[rows];  // in the visited map, 0 for unvisited, 1 for visited, 2 for marked mine.

  for (int i = 0; i < rows; ++i) {
    initial_map[i] = new int[columns];
    visited_map[i] = new int[columns];
  }

  // std::cout << "rows: " << rows << " columns: " << columns << std::endl;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      char c;
      std::cin >> c;
      if (c == 'X') {
        initial_map[i][j] = -1;
        InitMark(i, j);
        total_mines++;
      }
      visited_map[i][j] = 0;
    }
  }
}

/**
 * @brief The definition of function VisitBlock(int, int)
 *
 * @details This function is designed to visit a block in the game map. We take the 3 * 3 game map above as an example.
 * At the beginning, if you call VisitBlock(0, 0), the return value would be 0 (game continues), and the game map would
 * be
 *     1??
 *     ???
 *     ???
 * If you call VisitBlock(0, 1) after that, the return value would be -1 (game ends and the players loses) , and the
 * game map would be
 *     1X?
 *     ???
 *     ???
 * If you call VisitBlock(0, 2), VisitBlock(2, 0), VisitBlock(1, 2) instead, the return value of the last operation
 * would be 1 (game ends and the player wins), and the game map would be
 *     1@1
 *     122
 *     01@
 *
 * @param r The row coordinate (0-based) of the block to be visited.
 * @param c The column coordinate (0-based) of the block to be visited.
 *
 * @note You should edit the value of game_state in this function. Precisely, edit it to
 *    0  if the game continues after visit that block, or that block has already been visited before.
 *    1  if the game ends and the player wins.
 *    -1 if the game ends and the player loses.
 *
 * @note For invalid operation, you should not do anything.
 */
void VisitBlock(int r, int c) {
  if (game_state != 0 || visited_map[r][c] != 0 || r < 0 || r >= rows || c < 0 || c >= columns) {
    return;
  }
  visited_map[r][c] = 1;
  if (initial_map[r][c] == 0) {
    visit_count++;
    for (int i = 0; i < 8; i++) {
      int next_r = r + direction_x[i];
      int next_c = c + direction_y[i];
      if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < columns && visited_map[next_r][next_c] == 0) {
        VisitBlock(next_r, next_c);
      }
    }
  } else if (initial_map[r][c] != -1) {  // not mine
    visit_count++;
  } else {  // mine
    game_state = -1;
  }
}

/**
 * @brief The definition of function MarkMine(int, int)
 *
 * @details This function is designed to mark a mine in the game map.
 * If the block being marked is a mine, show it as "@".
 * If the block being marked isn't a mine, END THE GAME immediately. (NOTE: This is not the same rule as the real
 * game) And you don't need to
 *
 * For example, if we use the same map as before, and the current state is:
 *     1?1
 *     ???
 *     ???
 * If you call MarkMine(0, 1), you marked the right mine. Then the resulting game map is:
 *     1@1
 *     ???
 *     ???
 * If you call MarkMine(1, 0), you marked the wrong mine(There's no mine in grid (1, 0)).
 * The game_state would be -1 and game ends immediately. The game map would be:
 *     1?1
 *     X??
 *     ???
 * This is different from the Minesweeper you've played. You should beware of that.
 *
 * @param r The row coordinate (0-based) of the block to be marked.
 * @param c The column coordinate (0-based) of the block to be marked.
 *
 * @note You should edit the value of game_state in this function. Precisely, edit it to
 *    0  if the game continues after visit that block, or that block has already been visited before.
 *    1  if the game ends and the player wins.
 *    -1 if the game ends and the player loses.
 *
 * @note For invalid operation, you should not do anything.
 */
void MarkMine(int r, int c) {
  if (game_state != 0 || visited_map[r][c] != 0 || r < 0 || r >= rows || c < 0 || c >= columns) {
    return;
  }
  if (initial_map[r][c] == -1) {
    marked_mine_count++;
    visited_map[r][c] = 2;
  } else {
    game_state = -1;
    visited_map[r][c] = 2;
  }
}

/**
 * @brief The definition of function AutoExplore(int, int)
 *
 * @details This function is designed to auto-visit adjacent blocks of a certain block.
 * See README.md for more information
 *
 * For example, if we use the same map as before, and the current map is:
 *     ?@?
 *     ?2?
 *     ??@
 * Then auto explore is available only for block (1, 1). If you call AutoExplore(1, 1), the resulting map will be:
 *     1@1
 *     122
 *     01@
 * And the game ends (and player wins).
 */

int CountMine(int r, int c) {
  int marked_mine_around = 0;
  for (int i = 0; i < 8; i++) {
    int next_r = r + direction_x[i];
    int next_c = c + direction_y[i];
    if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < columns && visited_map[next_r][next_c] == 2) {
      marked_mine_around++;
    }
  }
  return marked_mine_around;
}

void AutoExplore(int r, int c) {
  if (game_state != 0 || visited_map[r][c] != 1 || initial_map[r][c] == -1 || r < 0 || r >= rows || c < 0 || c >= columns) {
    return;
  }
  int marked_mine_around = CountMine(r, c);
  if (marked_mine_around == initial_map[r][c]) {
    for (int i = 0; i < 8; i++) {
      int next_r = r + direction_x[i];
      int next_c = c + direction_y[i];
      if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < columns && visited_map[next_r][next_c] == 0) {
        VisitBlock(next_r, next_c);
        if (game_state != 0) {
          return;
        }
      }
    }
  }
}

/**
 * @brief The definition of function ExitGame()
 *
 * @details This function is designed to exit the game.
 * It outputs a line according to the result, and a line of two integers, visit_count and marked_mine_count,
 * representing the number of blocks visited and the number of marked mines taken respectively.
 *
 * @note If the player wins, we consider that ALL mines are correctly marked.
 */
void ExitGame() {
  // free the memory
  for (int i = 0; i < rows; ++i) {
    delete[] initial_map[i];
    delete[] visited_map[i];
  }
  delete[] initial_map;
  delete[] visited_map;

  if (game_state == 1) {
    std::cout << "YOU WIN!" << std::endl;
  } else {
    std::cout << "GAME OVER!" << std::endl;
  }

  std::cout << visit_count << " " << marked_mine_count << std::endl;

  exit(0);  // Exit the game immediately
}

/**
 * @brief The definition of function PrintMap()
 *
 * @details This function is designed to print the game map to stdout. We take the 3 * 3 game map above as an example.
 * At the beginning, if you call PrintMap(), the stdout would be
 *    ???
 *    ???
 *    ???
 * If you call VisitBlock(2, 0) and PrintMap() after that, the stdout would be
 *    ???
 *    12?
 *    01?
 * If you call VisitBlock(0, 1) and PrintMap() after that, the stdout would be
 *    ?X?
 *    12?
 *    01?
 * If the player visits all blocks without mine and call PrintMap() after that, the stdout would be
 *    1@1
 *    122
 *    01@
 * (You may find the global variable game_state useful when implementing this function.)
 *
 * @note Use std::cout to print the game map, especially when you want to try the advanced task!!!
 */
void PrintMap() {
  // if the leftover block count is equal to the mine count, game ends and player wins
  if (visit_count == rows * columns - total_mines) {
    game_state = 1;
    marked_mine_count = total_mines;
  }

  if (game_state == 1) {  // the winning state output
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        if (initial_map[i][j] == -1) {
          std::cout << "@";
        } else {
          std::cout << initial_map[i][j];
        }
      }
      std::cout << std::endl;
    }
    return;
  } else {  // otherwise
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        if (visited_map[i][j] == 0) {  // unvisited
          std::cout << "?";
        } else if (visited_map[i][j] == 2) {  // marked mine
          if (initial_map[i][j] == -1) {
            std::cout << "@";
          } else {
            std::cout << "X";
          }
        } else {
          if (initial_map[i][j] == -1) {  // visited, but not marked as mine
            std::cout << "X";
          } else {
            std::cout << initial_map[i][j];
          }
        }
      }
      std::cout << std::endl;
    }
  }
}

#endif
