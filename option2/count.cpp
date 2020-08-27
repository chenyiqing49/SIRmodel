#include "board.hpp"

int count_S(SIR::Board const &board) {
  int S =0;
  for (int i = 0; i != board.size(); ++i) {
    for (int j = 0; j != board.size(); ++j) {
      if (board(i, j).is_S()) {
        ++S;
      }
    }
  }
  return S;
}

int count_I(SIR::Board const &board) {
  int I = 0;
  for (int i = 0; i != board.size(); ++i) {
    for (int j = 0; j != board.size(); ++j) {
      if (board(i, j).is_I()) {
        ++I;
      }
    }
  }
  return I;
}

int count_R(SIR::Board const &board) {
  int R = 0;
  for (int i = 0; i != board.size(); ++i) {
    for (int j = 0; j != board.size(); ++j) {
      if (board(i, j).is_R()) {
        ++R;
      }
    }
  }
  return R;
}
