#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "sir.cpp"

TEST_CASE("Test Epidemy") {
  constexpr int day = 60;
  SIR s0{};
  s0.susceptible = 900.;
  s0.infectious = 100.;
  s0.recovered = 0.;
  Epidemy e1{s0, day};
  auto e = e1.create_model(0.00035, 0.12, 1000);
  CHECK_NOTHROW(e1.create_model(0.00035, 0.12, 1000));

  constexpr int day_ = 70;
  SIR s1{};
  s1.susceptible = 1900.;
  s1.infectious = 100.;
  s1.recovered = 0.;
  Epidemy e2{s1, day_};
  auto e_ = e2.create_model(0.00018, 0.12, 2000);
  CHECK_NOTHROW(e2.create_model(0.00018, 0.12, 2000));
}
