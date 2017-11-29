/*
 * Eviatar Natan
 * 307851808
 */
/*
 * ReversiLogic.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: eviatar
 */

#include "ReversiLogic.h"
#include <iostream>
using namespace std;
ReversiLogic::ReversiLogic() {
  // TODO Auto-generated constructor stub

}
 void ReversiLogic::availableMoves(vector<Point>& points,Board*& board,
     char &symbol,char &other_symbol) {
  verticalMoves(board, points, symbol, other_symbol);
  horizontalMoves(board, points, symbol, other_symbol);
  topDiagonalMoves(board, points, symbol, other_symbol);
  bottomDiagonalMoves(board, points, symbol, other_symbol);

}
int ReversiLogic::flipDiscs(Board*& board,Point &ref_point,
    char&symbol,char &other_symbol) {
  int counter = 0;
  int&count_ref = counter;
  verticalFlip(board, count_ref, ref_point, symbol, other_symbol);
  horizontalFlip(board, count_ref, ref_point, symbol, other_symbol);
  topDiagonalFlip(board, count_ref, ref_point, symbol, other_symbol);
  bottomDiagonalFlip(board, count_ref, ref_point, symbol, other_symbol);
  return counter;
}
void ReversiLogic::sortPoints(vector<Point>& moves) {
  //sort by x value
  for (unsigned int i = 0; i < moves.size() - 1; i++) {
    for (unsigned int j = i + 1; j < moves.size(); j++) {
      if (moves.at(i).getPointX() > moves.at(j).getPointX()) {
        Point p(moves.at(i).getPointX(), moves.at(i).getPointY());
        moves.at(i).setPointX(moves.at(j).getPointX());
        moves.at(i).setPointY(moves.at(j).getPointY());
        moves.at(j).setPointX(p.getPointX());
        moves.at(j).setPointY(p.getPointY());
      }
    }
  }
  //sort by y value
  for (unsigned int i = 0; i < moves.size() - 1; i++) {
    for (unsigned int j = i + 1; j < moves.size(); j++) {
      if (moves.at(i).getPointY() > moves.at(j).getPointY()
          &&moves.at(i).getPointX() == moves.at(j).getPointX()) {
        Point p(moves.at(i).getPointX(), moves.at(i).getPointY());
        moves.at(i).setPointX(moves.at(j).getPointX());
        moves.at(i).setPointY(moves.at(j).getPointY());
        moves.at(j).setPointX(p.getPointX());
        moves.at(j).setPointY(p.getPointY());
      }
    }
  }
}
void ReversiLogic::removeDuplicatePoints(vector<Point>&moves) {
  for (unsigned int i = 0; i < moves.size() - 1; i++) {
    for (unsigned int j = i + 1; j < moves.size(); j++){
      if (moves.at(i).getPointY() == moves.at(j).getPointY()
          && moves.at(i).getPointX() == moves.at(j).getPointX()) {
        moves.erase(moves.begin() + j);
        j--;
      }
    }
  }
}
void ReversiLogic::verticalMoves(Board*&board, vector<Point> &moves,
    char &current, char &standby){
  //up
  const int row_size = board->getRowSize();
  const int column_size = board->getColumnSize();
  char** board_array = board->getBoardTable();
  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < column_size; j++) {
      if (board_array[i][j] == current) {
        int l = i - 1, m = j;
        if (l > 0) {
          if (board_array[l][m] == standby && l > 0) {
            while (board_array[l][m] == standby && l > 0)
              l--;
            if (board_array[l][m] == ' ') {
              Point point(l + 1, m + 1);
              moves.push_back(point);
            }
          }
        }
      }
    }
  }
  //down
  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < column_size; j++) {
      if (board_array[i][j] == current) {
        int l = i + 1, m = j;
        if (l < row_size) {
          if (board_array[l][m] == standby && l < row_size) {
            while (board_array[l][m] == standby && l < row_size) {
              l++;
              if (l >= row_size) {
                break;
              }
            }
            if (l < row_size){
              if (board_array[l][m] == ' ') {
                Point point(l + 1, m + 1);
                moves.push_back(point);
              }
            }
          }
        }
      }
    }
  }
}
void ReversiLogic::horizontalMoves(Board*&board, vector<Point> &moves,
    char &current, char &standby){
  //right
  const int row_size = board->getRowSize();
  const int column_size = board->getColumnSize();
  char** board_array = board->getBoardTable();
  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < column_size; j++) {
      if (board_array[i][j] == current) {
        int l = i,m = j + 1;
        if (m < column_size-1) {
          if (board_array[l][m] == standby && m < column_size - 1) {
            while (board_array[l][m] == standby && m < column_size - 1) {
              m++;
            }
            if (m < column_size){
              if (board_array[l][m] == ' '){
                Point point(l + 1, m + 1);
                moves.push_back(point);
              }
            }
          }
        }
      }
    }
  }
  //left
  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < column_size; j++) {
      if (board_array[i][j] == current) {
        int l = i, m = j - 1;
        if (m > 0) {
          if (board_array[l][m] == standby && m > 0) {
            while (board_array[l][m] == standby && m > 0)
              m--;
            if (board_array[l][m] == ' ') {
              Point point(l + 1, m + 1);
              moves.push_back(point);
            }
          }
        }
      }
    }
  }
}
void ReversiLogic::topDiagonalMoves(Board*&board,vector<Point> &moves,
    char &current,char &standby) {
  //top left
  const int row_size = board->getRowSize();
  const int column_size = board->getColumnSize();
  char** board_array = board->getBoardTable();
  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < column_size; j++) {
      if (board_array[i][j] == current) {
        int l = i - 1, m = j - 1;
        if (l > 0 && m > 0) {
          if (board_array[l][m] == standby && l > 0 && m > 0) {
            while (board_array[l][m] == standby && l > 0 && m > 0){
              l--;
              m--;
            }
            if (m < column_size) {
              if (board_array[l][m] == ' ') {
                Point point(l + 1, m + 1);
                moves.push_back(point);
              }
            }
          }
        }
      }
    }
  }
  //top right
  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < column_size; j++){
      if (board_array[i][j] == current) {
        int l = i - 1,m = j + 1;
        if (l > 0 && m < column_size) {
          if (board_array[l][m] == standby && l > 0 && m < column_size - 1) {
            while (board_array[l][m] == standby && l > 0
                && m < column_size - 1) {
              l--;
              m++;
            }
            if (board_array[l][m] == ' ') {
              Point point(l + 1, m + 1);
              moves.push_back(point);
            }
          }
        }
      }
    }
  }
}
void ReversiLogic::bottomDiagonalMoves(Board*&board,vector<Point> &moves,
    char &current,char &standby){
  //bottom left
  const int row_size = board->getRowSize();
  const int column_size = board->getColumnSize();
  char** board_array = board->getBoardTable();
  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < column_size; j++) {
      if (board_array[i][j] == current) {
        int l = i + 1, m = j - 1;
        if (l < row_size && m >= 0) {
          if (board_array[l][m] == standby && l < row_size && m >= 0) {
            while (board_array[l][m] == standby && l < row_size && m >= 0) {
              l++;
              m--;
              if (l >= row_size || m < 0) {
                break;
              }
            }
            if (l < row_size && m >= 0) {
              if (board_array[l][m] == ' ') {
                Point point(l + 1, m + 1);
                moves.push_back(point);
              }
            }
          }
        }
      }
    }
  }
  //bottom right
  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < column_size; j++) {
      if (board_array[i][j] == current) {
        int l = i + 1, m = j + 1;
        if (l < row_size && m < column_size) {
          if (board_array[l][m] == standby && l < row_size
              && m < column_size) {
            while (board_array[l][m] == standby && l < row_size
                && m < column_size) {
              l++;
              m++;
              if (l >= row_size || m >= column_size) {
                break;
              }
            }
            if (l < row_size && m < column_size) {
              if (board_array[l][m] == ' ') {
                Point point(l + 1, m + 1);
                moves.push_back(point);
              }
            }
          }
        }
      }
    }
  }
}
void ReversiLogic::verticalFlip(Board*& board, int& counter, Point&ref_point,
    char &current, char &standby) {
  //top
  int i = ref_point.getPointX() - 2;
  int j = ref_point.getPointY() - 1;
  const int row_size = board->getRowSize();
  char** board_array = board->getBoardTable();
  board_array[i + 1][j] = current;
  if (i >= 0) {
    if (board_array[i][j] == standby && i > 0){
      while (board_array[i][j] == standby && i > 0) {
        i--;
      }
      if (board_array[i][j] == current) {
        for (int l = ref_point.getPointX() - 2; l > i; l--) {
          counter++;
          board_array[l][j] = current;
        }
      }
    }
  }
  //down
  i = ref_point.getPointX();
  j = ref_point.getPointY() - 1;
  if (i < row_size) {
    if (board_array[i][j] == standby && i < row_size) {
      while (board_array[i][j] == standby && i < row_size) {
        i++;
        if (i >= row_size) {
          return;
        }
      }
      if (board_array[i][j] == current) {
        for (int l = ref_point.getPointX(); l < i; l++) {
          counter++;
          board_array[l][j] = current;
        }
      }
    }
  }
}
void ReversiLogic::horizontalFlip(Board*& board,int& counter,Point&ref_point,
    char &current, char &standby) {
  //left
  int i = ref_point.getPointX() - 1;
  int j = ref_point.getPointY() - 2;
  const int column_size = board->getColumnSize();
  char** board_array = board->getBoardTable();
  if (j >= 0) {
    if (board_array[i][j] == standby && j > 0) {
      while (board_array[i][j] == standby && j > 0) {
        j--;
      }
      if (board_array[i][j] == current) {
        for (int m = ref_point.getPointY() - 2; m > j; m--) {
          counter++;
          board_array[i][m] = current;
        }
      }
    }
  }
  //right
  i = ref_point.getPointX() - 1;
  j = ref_point.getPointY();
  if (j < column_size - 1) {
    if (board_array[i][j] == standby && j < column_size - 1) {
      while (board_array[i][j] == standby && j < column_size - 1) {
        j++;
      }
      if (j < column_size) {
        if (board_array[i][j] == current) {
          for (int m = ref_point.getPointY();m < j; m++) {
            counter++;
            board_array[i][m] = current;
          }
        }
      }
    }
  }
}
void ReversiLogic::topDiagonalFlip(Board*& board, int& counter,
    Point&ref_point, char &current, char &standby) {
  //top left
  int i = ref_point.getPointX() - 2;
  int j = ref_point.getPointY() - 2;
  const int column_size = board->getColumnSize();
  char** board_array=board->getBoardTable();
  if (j >= 0 && i >= 0) {
    if (board_array[i][j] == standby && j > 0 && i > 0) {
      while (board_array[i][j] == standby && i > 0 && j > 0) {
        i--;
        j--;
      }
      if (board_array[i][j] == current) {
        int l = ref_point.getPointX() - 2;
        int m = ref_point.getPointY() - 2;
        while (l > i && m > j) {
          board_array[l][m] = current;
          l--;
          m--;
          counter++;
        }
      }
    }
  }
  //top right
  i = ref_point.getPointX() - 2;
  j = ref_point.getPointY();
  if (i >= 0 && j < column_size) {
    if (board_array[i][j] == standby && j < column_size - 1 && i > 0) {
      while (board_array[i][j] == standby && i > 0 && j < column_size - 1) {
        i--;
        j++;
      }
      if (i >= 0 && j < column_size) {
        if (board_array[i][j] == current) {
          int l = ref_point.getPointX() - 2;
          int m = ref_point.getPointY();
          while (l > i && m < j) {
            board_array[l][m] = current;
            l--;
            m++;
            counter++;
          }
        }
      }
    }
  }
}
void ReversiLogic::bottomDiagonalFlip(Board*& board, int& counter,
    Point&ref_point, char &current, char &standby) {
  //bottom left
  int i = ref_point.getPointX();
  int j = ref_point.getPointY() - 2;
  const int row_size = board->getRowSize();
  const int column_size = board->getColumnSize();
  char** board_array = board->getBoardTable();
  if (j >= 0 && i < row_size) {
    if (board_array[i][j] == standby && j > 0 && i < row_size) {
      while (board_array[i][j] == standby && i < row_size && j > 0) {
        i++;
        j--;
        if (i >= row_size || j <= 0) {
          break;
        }
      }
      if (i < row_size && j >= 0) {
        if (board_array[i][j] == current) {
          int l = ref_point.getPointX();
          int m = ref_point.getPointY() - 2;
          while (l < i && m > j) {
            board_array[l][m] = current;
            l++;
            m--;
            counter++;
          }
        }
      }
    }
  }
  //bottom right
  i = ref_point.getPointX();
  j = ref_point.getPointY();
  if (j < column_size && i < row_size) {
    if (board_array[i][j] == standby && j < column_size && i < row_size) {
      while (board_array[i][j] == standby && i < row_size && j < column_size) {
        i++;
        j++;
        if (i >= row_size || j >= column_size) {
          break;
        }
      }
      if (i < row_size && j < column_size) {
        if (board_array[i][j] == current) {
          int l = ref_point.getPointX();
          int m = ref_point.getPointY();
          while (l < i && m < j) {
            counter++;
            board_array[l][m] = current;
            l++;
            m++;
          }
        }
      }
    }
  }
}

ReversiLogic::~ReversiLogic() {
  // TODO Auto-generated destructor stub
}
