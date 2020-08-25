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

  Person operator()(int i, int j) const {
    Person p;
    return (i >= 0 && i < n_ && j >= 0 && j < n_) ? board_[i * n_ + j] : p;
  }

  Person &operator()(int i, int j) {
    assert(i >= 0 && i < n_ && j >= 0 && j < n_);
    return board_[i * n_ + j];
  }

  int size() const { return n_; }
};
} // namespace SIR

#endif
