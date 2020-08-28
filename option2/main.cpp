#include "board.hpp"
#include "count.cpp"
#include "display.hpp"
#include "evolve.cpp"
#include "point.hpp"
#include <chrono>
#include <thread>

int main() {
  constexpr int dim = 256;
  SIR::Board board{dim};
  SIR::Display display{dim};

    //Infect cells clicked by mouse
  while (display.wait_key()) {
    display.draw(board);
    auto p1 = display.getMousePosition();
    int X = p1.x / display.getCellSize();
    int Y = p1.y / display.getCellSize();
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

    //-- std::vector<SIR::Point> pointsS{};
    //-- std::vector<SIR::Point> pointsI{};
    //-- std::vector<SIR::Point> pointsR{};

    {
        //set the origin
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

    for (int i = 0; i != d; ++i) { //valutare se modificare il valore d oppure impostare un while o un break se raggiunto I_value=0
        int S_value = count_S(board);
        int I_value = count_I(board);
        int R_value = count_R(board);
        
        //print S, I, and R values on user's console
      std::cout << "\033c";
      std::cout << "S: " << S_value << '\n'
                << "I: " << I_value << '\n'
                << "R: " << R_value << '\n';

      SIR::Point p1{i, S_value};
     //-- pointsS.push_back(p1);

      SIR::Point p2{i, I_value};
     //-- pointsI.push_back(p2);

      SIR::Point p3{i, R_value};
     //-- pointsR.push_back(p3);

      board = evolve(board);
      display.draw(board);

        //draw points on graph window
      constexpr auto radius = 1.f;

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
    sf::Event event;
    while (window1.waitEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window1.close();
        break;
      }
    }
  }
}
