#include "sir.hpp"
#include <cassert>

// Declaration and definition of member functions
SIR Epidemy::getInit() { return init_; }

int Epidemy::getNday() { return n_day_; }

std::vector<SIR> Epidemy::create_model(double const &beta, double const &gamma,
                                       int const &N) {
  assert(n_day_ > 0);
  assert(beta > 0);
  assert(gamma > 0);

  std::vector<SIR> result{init_};

  for (int i = 1; i < n_day_; ++i) {
    auto const &prev = result.back();
    SIR s;
    s.susceptible =
        prev.susceptible - beta * prev.infectious * prev.susceptible;
    s.infectious = prev.infectious + beta * prev.infectious * prev.susceptible -
                   gamma * prev.infectious;
    s.recovered = N - s.susceptible - s.infectious;
    result.push_back(s);
  }
  return result;
}
