#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "point.cpp"

TEST_CASE("Testing Point") {
  CHECK(Point{0, 0.} == Point{0, 0.});
  CHECK(Point{1, 0.} != Point{0, 1.});
  CHECK(Point{0, 1.} != Point{1, 0.});
}
