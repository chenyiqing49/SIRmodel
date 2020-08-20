#ifndef SIR_DISPLAY_HPP
#define SIR_DISPLAY_HPP

#include "board.hpp"
#include <SFML/Graphics.hpp>

namespace SIR {
class Display {
  int m_board_side;
  sf::RenderWindow m_window;

  static constexpr int s_cell_size = 4;

  static int display_side(int board_side) {
    // don't show the borders of the board
    return (board_side - 6) * s_cell_size;
  }

  static constexpr auto s_window_title = "SIR";

public:
  Display(int board_side)
      : m_board_side{board_side}, m_window{
                                      sf::VideoMode(display_side(board_side),
                                                    display_side(board_side)),
                                      s_window_title, sf::Style::Close} {}

  void draw(Board const &board) {
    assert(m_board_side == board.size());

    m_window.clear(sf::Color::Black);

    sf::RectangleShape rectS(sf::Vector2f(s_cell_size, s_cell_size));
    rectS.setFillColor(sf::Color::Red);
    rectS.setOutlineThickness(1.f);
    rectS.setOutlineColor(sf::Color::Black);

    sf::RectangleShape rectI(sf::Vector2f(s_cell_size, s_cell_size));
    rectI.setFillColor(sf::Color::Green);
    rectI.setOutlineThickness(1.f);
    rectI.setOutlineColor(sf::Color::Black);

    sf::RectangleShape rectR(sf::Vector2f(s_cell_size, s_cell_size));
    rectR.setFillColor(sf::Color::Blue);
    rectR.setOutlineThickness(1.f);
    rectR.setOutlineColor(sf::Color::Black);

    int const N = board.size();

    for (int i = 3; i != N - 3; ++i) {
      for (int j = 3; j != N - 3; ++j) {
        if (board(i, j).is_I()) {
          // note inversion of i and j
          rectI.setPosition((j - 3) * s_cell_size, (i - 3) * s_cell_size);
          m_window.draw(rectI);
        } else if (board(i, j).is_S()) {
          rectS.setPosition((j - 3) * s_cell_size, (i - 3) * s_cell_size);
          m_window.draw(rectS);
        } else if (board(i, j).is_R()) {
          rectR.setPosition((j - 3) * s_cell_size, (i - 3) * s_cell_size);
          m_window.draw(rectR);
        }
      }
    }

    m_window.display();
  }

  void wait_key_pressed() {
    sf::Event event;

    m_window.waitEvent(event);
    while (event.type != sf::Event::KeyPressed) {
      m_window.waitEvent(event);
    }
  }
};

} // namespace SIR

#endif
