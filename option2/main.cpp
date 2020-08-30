#include "board.hpp"
#include "count.cpp"
#include "display.hpp"
#include "evolve.cpp"
#include "point.hpp"
#include <chrono>
#include <thread>

int main() {
  constexpr int dim = 256;
  const int N = dim * dim;

  SIR::Board board{dim};
  SIR::Display display{dim};

  std::cout << "Insert infect cells with mouse's left button...\n";
  std::cout << "Press any key to start the animation\n";

  // Infect cells clicked by mouse
  while (display.wait_key() == true) {
    int const c_size = display.getCellSize();
    display.draw(board);
    auto p1 = display.getMousePosition();
    int X = p1.x / c_size;
    int Y = p1.y / c_size;
    board(Y, X).infectSure();
  }

  constexpr int d = 700;

  constexpr int window_width = d + 20;
  constexpr int window_height = d + 20;
  constexpr int point_min_x = 0;
  constexpr int point_max_x = d;
  constexpr double point_min_y = 0;
  constexpr double point_max_y = dim * dim;

  // create the window whit the dynamic graph
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window1(sf::VideoMode(window_width, window_height),
                           "SIR graphs", sf::Style::Default, settings);

  // (lambda) function to convert a point to the coordinates of the SFML window
  auto to_window_frame = [](SIR::Point const &p) {
    // leave a ten-pixel border
    constexpr int inner_sep = 10;

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

    {
      // set the origin
      constexpr auto radius_O = 5.f;
      constexpr auto outline_thickness = 2.f;
      sf::CircleShape zero{radius_O};
      zero.setFillColor(sf::Color::Black);
      zero.setOutlineThickness(outline_thickness);
      zero.setOutlineColor(sf::Color::White);
      zero.setOrigin(sf::Vector2f{radius_O, radius_O});
      zero.move(to_window_frame({0, 0}));
      window1.draw(zero);
    }

    // vector that contains S and R values
    std::vector<int> s{N};
    std::vector<int> r{0};

    for (int i = 0; i != d; ++i) {
      // search the previous value
      int const &prevS = s.back();
      int const &prevR = r.back();

      int countS = count_S(board);
      int countI = count_I(board);
      int countR = count_R(board);

      if (countI == 0) {
        break;
      } else {
        s.push_back(countS);
        r.push_back(countR);

        // through the formulas of the SIR model we obtain
        // the values of beta, gamma and R_0
        double b_num = static_cast<double>(prevS - countS);
        double b_den = static_cast<double>(countS * countI);
        double beta = b_num / b_den;

        double g_num = static_cast<double>(countR - prevR);
        double g_den = static_cast<double>(countI);
        double gamma = g_num / g_den;

        double R_0 = N * (beta / gamma);

        // print S, I, R, beta, gamma and R_0 values on user's console
        std::cout << "\033c";
          std::cout << "S: " << countS << '\n'
                    << "I: " << countI << '\n'
                    << "R: " << countR << '\n'
                    << "BETA: " << beta << '\n'
                    << "GAMMA: " << gamma << '\n'
                    << "R_0: " << R_0 << '\n';
        }

        // define three points
        SIR::Point p1{i, countS};
        SIR::Point p2{i, countI};
        SIR::Point p3{i, countR};

        board = evolve(board);
        display.draw(board);

        // draw points on graph window
        constexpr auto radius = 2.f;

        sf::CircleShape c1{radius};
        c1.setFillColor(sf::Color::Red);
        c1.setOrigin(sf::Vector2f{radius, radius});
        c1.move(to_window_frame(p1));
        window1.draw(c1);

        sf::CircleShape c2{radius};
        c2.setFillColor(sf::Color::Green);
        c2.setOrigin(sf::Vector2f{radius, radius});
        c2.move(to_window_frame(p2));
        window1.draw(c2);

        sf::CircleShape c3{radius};
        c3.setFillColor(sf::Color::Blue);
        c3.setOrigin(sf::Vector2f{radius, radius});
        c3.move(to_window_frame(p3));
        window1.draw(c3);

        window1.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
      }
    }
    sf::Event event;
    while (window1.waitEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window1.close();
        break;
      }
    }
    display.wait_event();
  }
}
