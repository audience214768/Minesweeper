#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <utility>
#include<vector>

extern int rows;         // The count of rows of the game map.
extern int columns;      // The count of columns of the game map.
extern int total_mines;  // The count of mines of the game map.

// You MUST NOT use any other external variables except for rows, columns and total_mines.

const int shift_x[8] = {-1, 0, 1, -1, 1, -1, 0, 1},
          shift_y[8] = {-1, -1, -1, 0, 0, 1, 1, 1}; //convient to traverse around

std::vector<std::vector<int>> map; //-2 for unknown, -1 for mine , n for num of the mines around

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
  // TODO (student): Initialize all your global variables!
  int first_row, first_column;
  std::cin >> first_row >> first_column;
  Execute(first_row, first_column, 0);
  map.resize(rows, std::vector<int>(columns, 0));
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
  // TODO (student): Implement me!
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      char ch = getchar();
      if(ch >= '0' && ch < '9') {
        map[i][j] = ch - '0';
      } else {
        if(ch == '?') {
          map[i][j] = -2;
        } else {
          map[i][j] = -1;
        }
      }
    }
  }
}

/**
 * @brief The definition of function Decide()
 *
 * @details This function is designed to decide the next step when playing the client's (or player's) role. Open up your
 * mind and make your decision here! Caution: you can only execute once in this function.
 */
void Decide() {
  // TODO (student): Implement me!
  // while (true) {
  //   Execute(0, 0);
  // }
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      if(map[i][j] > '0' && map[i][j] < '9') {
        int total_mines = map[i][j], unknow_grid = 0;
        for(int k = 0; k < 8; k++) {
          int x = i + shift_x[k], y = j + shift_y[k];
          if(map[x][y] == -2) 
        }
      }
    }
  }
}

#endif