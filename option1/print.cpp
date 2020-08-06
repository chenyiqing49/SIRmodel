#include "sir.hpp"
#include <iostream>

void print_epidemy(std::vector<SIR> const &epidemy) {
  
  std::cout << "S, I, R\n";
  for (auto &i : epidemy) {
    std::cout << i.susceptible << ", " << i.infectious << ", " << i.recovered
              << '\n';
  }

  std::cout << "\n\n";
  std::cout << "*-------------------| SFML |-------------------*\n";
  std::cout << "RED -> Number of susceptible during the epidemy\n";
  std::cout << "GREEN -> Number of infected during the epidemy\n";
  std::cout << "BLUE -> Number of recovered during the epidemy\n";
  std::cout << "*----------------------------------------------*\n";
}

