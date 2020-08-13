#ifndef SIR_BOARD_HPP
#define SIR_BOARD_HPP

#include "person.hpp"
#include <cassert>
#include <iostream>
#include <vector>

namespace SIR {
class Board {
private:
  int n_;
  std::vector<Person> board_;

public:
  Board(int n) : n_{n}, board_(n * n) {}

  auto getPopulation() { return board_; }

  Person operator()(int i, int j) const {
    Person p;
    return (i >= 0 && i < n_ && j >= 0 && j < n_) ? board_[i * n_ + j] : p;
  }

  Person &operator()(int i, int j) {
    assert(i >= 0 && i < n_ && j >= 0 && j < n_);
    return board_[i * n_ + j];
  }

  int size() const { return n_; }

  void print() {
    std::cout << "\033c";
    for (int i = 0; i != n_; ++i) {
      for (int j = 0; j != n_; ++j) {
        char c;

        if (board_[i * n_ + j].is_S()) {
          c = '-';
        } else if (board_[i * n_ + j].is_I()) {
          c = '+';
        } else if (board_[i * n_ + j].is_R()) {
          c = '*';
        }
        std::cout << c << ' ';
      }
      std::cout << '\n';
    }
  }
};
} // namespace SIR

#endif
