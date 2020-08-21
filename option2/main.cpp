#include "board.hpp"
#include "count.cpp"
#include "display.hpp"
#include "evolve.cpp"
#include "point.hpp"
#include <chrono>
#include <thread>

int main() {
  constexpr int dim = 220;
  SIR::Board board{dim};
  SIR::Display display{dim};

  board(114, 114).infect();
  board(113, 113).infect();
  board(114, 113).infect();
  board(115, 113).infect();
  board(116, 114).infect();

  display.draw(board);
  std::cout << "Press any key to start the animation.\n";
  display.wait_key_pressed();

  // constexpr int d = 500;

  constexpr int window_width = 700;
  constexpr int window_height = 700;
  constexpr int point_min_x = 0;
  constexpr int point_max_x = 600;
  constexpr double point_min_y = 0;
  constexpr double point_max_y = 48400;

  // create the window
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window1(sf::VideoMode(window_width, window_height),
                           "SIR graphs", sf::Style::Default, settings);

  // (lambda) function to convert a point to the coordinates of the SFML window
  auto to_window_frame = [](SIR::Point const &p) {
    // leave a ten-pixel border
    constexpr int inner_sep = 30;

    constexpr int canvas_width = window_width - 2 * inner_sep;
    constexpr int canvas_height = window_height - 2 * inner_sep;
    constexpr auto x_scale = canvas_width / (point_max_x - point_min_x);
    constexpr auto y_scale = canvas_height / (point_max_y - point_min_y);

    return sf::Vector2f((p.x - point_min_x) * x_scale + inner_sep,
                        canvas_height + inner_sep -
                            (p.y - point_min_y) * y_scale);
  };

  if (window1.isOpen()) {
    window1.clear(sf::Color::Black);

    std::vector<SIR::Point> pointsS{};
    std::vector<SIR::Point> pointsI{};
    std::vector<SIR::Point> pointsR{};

    {
      constexpr auto radius = 5.f;
      constexpr auto outline_thickness = 2.f;
      sf::CircleShape zero{radius};
      zero.setFillColor(sf::Color::Black);
      zero.setOutlineThickness(outline_thickness);
      zero.setOutlineColor(sf::Color::White);
      zero.setOrigin(sf::Vector2f{radius, radius});
      zero.move(to_window_frame({0, 0}));
      window1.draw(zero);
    }

    for (int i = 0; i != 600; ++i) {
      std::cout << "\033c";
      std::cout << "S: " << count_S(board) << '\n'
                << "I: " << count_I(board) << '\n'
                << "R: " << count_R(board) << '\n';

      SIR::Point p1{i, count_S(board)};
      pointsS.push_back(p1);

      SIR::Point p2{i, count_I(board)};
      pointsI.push_back(p2);

      SIR::Point p3{i, count_R(board)};
      pointsR.push_back(p3);

      board = evolve(board);
      display.draw(board);

      for (auto const &p : pointsS) {
        constexpr auto radius = 2.f;
        sf::CircleShape c1{radius};
        c1.setFillColor(sf::Color::Red);
        c1.setOrigin(sf::Vector2f{radius, radius});
        c1.move(to_window_frame(p));
        window1.draw(c1);
      }

      for (auto const &p : pointsI) {
        constexpr auto radius = 2.f;
        sf::CircleShape c2{radius};
        c2.setFillColor(sf::Color::Green);
        c2.setOrigin(sf::Vector2f{radius, radius});
        c2.move(to_window_frame(p));
        window1.draw(c2);
      }

      for (auto const &p : pointsR) {
        constexpr auto radius = 2.f;
        sf::CircleShape c3{radius};
        c3.setFillColor(sf::Color::Blue);
        c3.setOrigin(sf::Vector2f{radius, radius});
        c3.move(to_window_frame(p));
        window1.draw(c3);
      }

      window1.display();
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    sf::Event event;
    while (window1.waitEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window1.close();
        break;
      }
    }
  }
}
