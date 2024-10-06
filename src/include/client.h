#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <utility>

extern int rows;         // The count of rows of the game map.
extern int columns;      // The count of columns of the game map.
extern int total_mines;  // The count of mines of the game map.

int map_state[30][30];

int directions_x[] = {0, 1, 0, -1, 1, 1, -1, -1};
int directions_y[] = {1, 0, -1, 0, 1, -1, 1, -1};

// You MUST NOT use any other external variables except for rows, columns and total_mines.

/**
 * @brief The definition of function Execute(int, int, bool)
 *
 * @details This function is designed to take a step when player the client's (or player's) role, and the implementation
 * of it has been finished by TA. (I hope my comments in code would be easy to understand T_T) If you do not understand
 * the contents, please ask TA for help immediately!!!
 *
 * @param r The row coordinate (0-based) of the block to be visited.
 * @param c The column coordinate (0-based) of the block to be visited.
 * @param type The type of operation to a certain block.
 * If type == 0, we'll execute VisitBlock(row, column).
 * If type == 1, we'll execute MarkMine(row, column).
 * If type == 2, we'll execute AutoExplore(row, column).
 * You should not call this function with other type values.
 */
void Execute(int r, int c, int type);

/**
 * @brief The definition of function InitGame()
 *
 * @details This function is designed to initialize the game. It should be called at the beginning of the game, which
 * will read the scale of the game map and the first step taken by the server (see README).
 */

void InitGame() {
  int first_row, first_column;
  std::cin >> first_row >> first_column;
  Execute(first_row, first_column, 0);
}

/**
 * @brief The definition of function ReadMap()
 *
 * @details This function is designed to read the game map from stdin when playing the client's (or player's) role.
 * Since the client (or player) can only get the limited information of the game map, so if there is a 3 * 3 map as
 * above and only the block (2, 0) has been visited, the stdin would be
 *     ???
 *     12?
 *     01?
 */
void ReadMap() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      char c;
      std::cin >> c;
      if (c == '?') {
        map_state[i][j] = -2;  // unknown
      } else if (c == '@') {
        map_state[i][j] = -1;  // marked as mine
      } else {
        map_state[i][j] = c - '0';
      }
    }
  }
  return;
}

/**
 * @brief The definition of function Decide()
 *
 * @details This function is designed to decide the next step when playing the client's (or player's) role. Open up your
 * mind and make your decision here!
 */

bool SearchPossibleMark();

bool DiscoverPatterns();

bool MarkBestPossibleBlock();

void RandomDecide();

void Decide() {
  if (!SearchPossibleMark()) {
    if (!DiscoverPatterns()) {
      if (!MarkBestPossibleBlock()) {
        RandomDecide();
      }
    }
  }
}

bool SearchPossibleMark() {
  // Without any trick, only mark the block when unknown blocks around == number of mines around
  bool found = false;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      if (map_state[r][c] > 0) {
        int mine_around = map_state[r][c];
        int unknown_blocks = 0;
        for (int i = 0; i < 8; i++) {
          int new_x = r + directions_x[i];
          int new_y = c + directions_y[i];
          if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < columns) {
            if (map_state[new_x][new_y] == -2) {
              unknown_blocks++;
            }
            if (map_state[new_x][new_y] == -1) {
              mine_around--;
            }
          }
        }
        map_state[r][c] = mine_around;
        if (mine_around == 0 && unknown_blocks > 0) {
          // std::cout << "Known-Explore " << r << " " << c << std::endl;  // debug
          Execute(r, c, 2);
          return true;
        }
        if (unknown_blocks == mine_around && mine_around > 0) {
          for (int i = 0; i < 8; i++) {
            int new_x = r + directions_x[i];
            int new_y = c + directions_y[i];
            if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < columns) {
              if (map_state[new_x][new_y] == -2) {
                // std::cout << "Known-MarkMine " << new_x << " " << new_y << std::endl;  // debug
                Execute(new_x, new_y, 1);
                return true;
              }
            }
          }
        }
      }
    }
  }
  return found;
}

bool DiscoverPatterns() {
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      if (map_state[r][c] == 1) {
        if (c + 1 < columns && map_state[r][c + 1] == 1) {
          // Horizontal 1-1
          if ((c + 1 == columns - 1 || c == 0) || (map_state[r + 1][c - 1] >= 0 && map_state[r - 1][c - 1] >= 0) ||
              (map_state[r + 1][c + 2] >= 0 && map_state[r - 1][c + 2] >= 0)) {
            int dx[6] = {1, 0, -1, 1, 0, -1};
            int dy[6] = {-1, -1, -1, 2, 2, 2};
            int count = 0;
            for (int count = 0; count < 6; count++) {
              if (r + dx[count] >= 0 && r + dx[count] < rows && c + dy[count] >= 0 && c + dy[count] < columns &&
                  map_state[r + dx[count]][c + dy[count]] == -2) {
                // std::cout << "Pattern-Discover " << r + dx[count] << " " << c + dy[count] << std::endl;  // debug
                Execute(r + dx[count], c + dy[count], 0);
                return true;
              }
            }
          }
        }
        if (r + 1 < rows && map_state[r + 1][c] == 1) {
          // Vertical 1-1
          if ((r + 1 == rows - 1 || r == 0) || (map_state[r - 1][c + 1] >= 0 && map_state[r - 1][c - 1] >= 0) ||
              (map_state[r + 2][c + 1] >= 0 && map_state[r + 2][c - 1] >= 0)) {
            int dx[6] = {-1, -1, -1, 2, 2, 2};
            int dy[6] = {1, 0, -1, 1, 0, -1};
            int count = 0;
            for (int count = 0; count < 6; count++) {
              if (r + dx[count] >= 0 && r + dx[count] < rows && c + dy[count] >= 0 && c + dy[count] < columns &&
                  map_state[r + dx[count]][c + dy[count]] == -2) {
                // std::cout << "Pattern-Discover " << r + dx[count] << " " << c + dy[count] << std::endl;  // debug
                Execute(r + dx[count], c + dy[count], 0);
                return true;
              }
            }
          }
        }
      }
    }
  }
  return false;
}

bool MarkBestPossibleBlock() {
  // Mark the block with the highest probability of being a mine
  double max_posibility = 0;
  int best_block[2] = {-1, -1};
  double possibility_map[30][30] = {0.0};
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (map_state[i][j] > 0) {
        int mine_around = map_state[i][j];
        int unknown_blocks = 0;
        for (int k = 0; k < 8; k++) {
          int new_x = i + directions_x[k];
          int new_y = j + directions_y[k];
          if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < columns) {
            if (map_state[new_x][new_y] == -2) {
              unknown_blocks++;
            }
            if (map_state[new_x][new_y] == -1) {
              mine_around--;
            }
          }
        }
        // set the unknown blocks around to have a possibility of being a mine
        if (mine_around > 0) {
          for (int k = 0; k < 8; k++) {
            int new_x = i + directions_x[k];
            int new_y = j + directions_y[k];
            if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < columns) {
              if (map_state[new_x][new_y] == -2) {
                possibility_map[new_x][new_y] += mine_around / (double)unknown_blocks;
              }
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (map_state[i][j] == -2 && possibility_map[i][j] > max_posibility) {
        max_posibility = possibility_map[i][j];
        best_block[0] = i;
        best_block[1] = j;
      }
    }
  }
  if ((best_block[0] == -1 && best_block[1] == -1) || max_posibility <= 0.5) {
    return false;
  }
  // std::cout << "Possibility-MarkMine " << best_block[0] << " " << best_block[1] << std::endl; // debug
  Execute(best_block[0], best_block[1], 1);
  map_state[best_block[0]][best_block[1]] = -1;
  return true;
}

void RandomDecide() {
  int r, c;
  srand(time(NULL));
  do {
    r = rand() % rows;
    c = rand() % columns;
  } while (map_state[r][c] != -2);
  // std::cout << "Random " << r << " " << c << std::endl; // debug
  Execute(r, c, 0);
}

#endif