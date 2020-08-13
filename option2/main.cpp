#include "board.hpp"
#include "display.hpp"
#include "evolve.cpp"
#include <chrono>
#include <thread>

int main() {
  int dim = 220;
  SIR::Board board{dim};

  board(5, 4).infect();
  board(4, 5).infect();
  board(6, 4).infect();
  board(6, 5).infect();

  board(100, 100).infect();
  board(101, 100).infect();

  board(205, 204).infect();
  board(204, 205).infect();
  board(206, 204).infect();
  board(206, 205).infect();

  SIR::Display display{dim};
  display.draw(board);
  std::cout << "Press any key to start the animation.\n";
  display.wait_key_pressed();

  for (int i = 0; i != 700; ++i) {
    board = evolve(board);
    display.draw(board);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}