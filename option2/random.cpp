#include <random>

int generateRandom(int const &inf, int const &sup) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(inf, sup);
  int rnd = distrib(gen);
  return rnd;
}
