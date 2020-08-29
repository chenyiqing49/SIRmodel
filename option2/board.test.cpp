#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "board.hpp"
#include "evolve.cpp"

TEST_CASE("Testing Board") {
  int dim = 220;
  SIR::Board board{dim};

  CHECK(board(0, 0) == board(0, 0));

  board(0, 1).infect();
  CHECK(board(0, 1) != board(1, 0));
  CHECK(board(1, 0) != board(0, 1));

  CHECK_NOTHROW(board(0, 1).infectSure());
  CHECK_NOTHROW(board(0, 1).update());
  CHECK_NOTHROW(evolve(board));
}
