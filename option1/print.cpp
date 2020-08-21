#include "sir.hpp"
#include <iostream>

void print_epidemy(std::vector<SIR> const &epidemy) {
  std::cout << "S, I, R\n";
  for (auto &i : epidemy) {
    std::cout << i.susceptible << ", " << i.infectious << ", " << i.recovered
              << '\n';
  }
}
