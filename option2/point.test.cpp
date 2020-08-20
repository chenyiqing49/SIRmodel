#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "point.hpp"

TEST_CASE("testing Point") {
  CHECK(SIR::Point{0, 0} == SIR::Point{0, 0});
  CHECK(SIR::Point{1, 0} != SIR::Point{0, 1});
  CHECK(SIR::Point{0, 1} != SIR::Point{1, 0});
}