#ifndef CLIENT_H
#define CLIENT_H

#include <algorithm>
#include <iostream>
#include <utility>
#include<vector>
#include<set>

extern int rows;         // The count of rows of the game map.
extern int columns;      // The count of columns of the game map.
extern int total_mines;  // The count of mines of the game map.

// You MUST NOT use any other external variables except for rows, columns and total_mines.

const int shift_x_client[8] = {-1, 0, 1, -1, 1, -1, 0, 1},
          shift_y_client[8] = {-1, -1, -1, 0, 0, 1, 1, 1}; //convient to traverse around

std::vector<std::vector<int>> grid; //-2 for unknown, -1 for mine , n for num of the mines around
std::vector<std::vector<double>> prob;

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
  grid.resize(rows, std::vector<int>(columns, -2));
  prob.resize(rows, std::vector<double>(columns, (double)total_mines / rows / columns));
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
  // TODO (student): Implement me!
  //std::cerr << rows << " " << columns << std::endl;
  int unknow_mine = total_mines, unknow_grid = 0;
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      char ch;
      std::cin >> ch;
      std::cerr << ch;
      if(ch >= '0' && ch < '9') {
        grid[i][j] = ch - '0';
      } else {
        if(ch == '?') {
          grid[i][j] = -2;
          unknow_grid++;
        } else {
          grid[i][j] = -1;
          unknow_mine--;
        }
      }
    }
    std::cerr << std::endl;
  }
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j <columns; j++)
      prob[i][j] = (double)unknow_mine / unknow_grid;
  }
}



bool Minus(int x1, int y1, int x2, int y2) {
  std::set<int> s1, s2;
  int unknow_mines1 = grid[x1][y1], unknow_mines2 = grid[x2][y2];
  for(int k = 0; k < 8; k++) {
    int x = x1 + shift_x_client[k], y = y1 + shift_y_client[k];
    if(x < 0 || x >= rows || y < 0 || y >= columns) {
      continue;
    }
    if(grid[x][y] == -2) {
      s1.insert(x * columns + y);
    } else {
      if(grid[x][y] == -1) {
        unknow_mines1--;
      }
    }
  }
  for(int k = 0; k < 8; k++) {
    int x = x2 + shift_x_client[k], y = y2 + shift_y_client[k];
    if(x < 0 || x >= rows || y < 0 || y >= columns) {
      continue;
    }
    if(grid[x][y] == -2) {
      s2.insert(x * columns + y);
    } else {
      if(grid[x][y] == -1) {
        unknow_mines2--;
      }
    }
  }
  std::set<int> s1_minus_s2, s2_minus_s1;                //calculate the A-B
  for(int index : s1) {
    if(!s2.count(index)) {
      s1_minus_s2.insert(index);
    }
  }
  for(int index : s2) {
    if(!s1.count(index)) {
      s2_minus_s1.insert(index);
    }
  }
  if(s1_minus_s2.size() == unknow_mines1 - unknow_mines2){
    for(int index : s1_minus_s2) {
      int x = index / columns, y = index % columns;
      if(grid[x][y] == -2) {
        Execute(x, y, 1);                 //all is the mine
        return 1;
      }
    }
    for(int index : s2_minus_s1) {
      int x = index / columns, y = index % columns;
      if(grid[x][y] == -2) {
        Execute(x, y, 0);                // all is safe
        return 1;
      }
    }
  }
  if(s2_minus_s1.size() == unknow_mines2 - unknow_mines1){
    for(int index : s2_minus_s1) {
      int x = index / columns, y = index % columns;
      if(grid[x][y] == -2) {
        Execute(x, y, 1);                 //all is the mine
        return 1;
      }
    }
    for(int index : s1_minus_s2) {
      int x = index / columns, y = index % columns;
      if(grid[x][y] == -2) {
        Execute(x, y, 0);                // all is safe
        return 1;
      }
    }
  }
  return 0;
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
  int choose_x = -1, choose_y = -1;
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      if(grid[i][j] > 0 && grid[i][j] < 9) {
        int unknow_mines = grid[i][j], unknow_grid = 0; 
        for(int k = 0; k < 8; k++) {
          int x = i + shift_x_client[k], y = j + shift_y_client[k];
          if(x < 0 || x >= rows || y < 0 || y >= columns) {
            continue;
          }
          if(grid[x][y] == -2) {
            unknow_grid ++;
          } else {
            if(grid[x][y] == -1) {
              unknow_mines--;
            } 
          }
        }
        if(unknow_mines == 0 && unknow_grid > 0) {                          //autoexplor if all the mines around is found
          Execute(i, j, 2);
          return ;
        }
        if(unknow_grid == unknow_mines) {                
          for(int k = 0; k < 8; k++) {
            int x = i + shift_x_client[k], y = j + shift_y_client[k];
            if(x < 0 || x >= rows || y < 0 || y >= columns) {
              continue;
            }
            if(grid[x][y] == -2) {                       //markmines if all the mines around is determined
              Execute(x, y, 1);
              return ;
            }
          }
        }
        for(int dx = -2; dx <= 2; dx++) {
          for(int dy = -2; dy <= 2; dy++) {
            int x = i + dx, y = j + dy;
            if(x < 0 || x >= rows || y < 0 || y >= columns || dx == 0 && dy == 0) continue;
            if(grid[x][y] > 0 && grid[x][y] < 9) {
              if(Minus(i, j, x, y)) {
                return ;
              }
            }
          }
        }
        for(int k = 0; k < 8; k++) {
          int x = i + shift_x_client[k], y = j + shift_y_client[k];
          if(x < 0 || x >= rows || y < 0 || y >= columns) {
            continue;
          }
          if(grid[x][y] == -2) {
            //std::cerr << x << " " << y << " " << (double)unknow_mines/unknow_grid << std::endl;
            prob[x][y] = std::max(prob[x][y], (double)unknow_mines / unknow_grid);
          }
        }  
      }
    }
  }
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++){
      if(grid[i][j] == -2) {
        if(choose_x == -1 || prob[choose_x][choose_y] > prob[i][j]) {
          choose_x = i;
          choose_y = j;
        }
      }
    }
  }
  Execute(choose_x, choose_y, 0);                        //visit the gird has lowest probability of mine
}

#endif