#include "point.hpp"
#include "print.cpp"
#include "sir.cpp"
#include <SFML/Graphics.hpp>

int main() {
  // Create new epidemy
  constexpr int day = 60;
  SIR s0{};
  s0.susceptible = 900.;
  s0.infectious = 100.;
  s0.recovered = 0.;
  Epidemy e1{s0, day};
  auto e = e1.create_model(0.00035, 0.12, 1000);
  print_epidemy(e);
  
  // Define size of the window SFML
  constexpr int window_width = 900;
  constexpr int window_height = 900;
  constexpr int point_min_x = 0;
  constexpr int point_max_x = day;
  constexpr double point_min_y = 0.;
  constexpr double point_max_y = 1000;
  
  // Loops that add points in a container
  std::vector<Point> pointsS{};
  for (int i = 0; i != day; ++i) {
    Point p1{i, e[i].susceptible};
    pointsS.push_back(p1);
  }

  std::vector<Point> pointsI{};
  for (int i = 0; i != day; ++i) {
    Point p2{i, e[i].infectious};
    pointsI.push_back(p2);
  }

  std::vector<Point> pointsR{};
  for (int i = 0; i != day; ++i) {
    Point p3{i, e[i].recovered};
    pointsR.push_back(p3);
  }

  // Create the window
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(window_width, window_height),
                          "SIR Model", sf::Style::Default, settings);

  // (lambda) Function to convert a point to the coordinates of the SFML window
  auto to_window_frame = [](Point const &p) {
    // Leave a thirty-pixel border
    constexpr int inner_sep = 30;

    constexpr int canvas_width = window_width - 2 * inner_sep;
    constexpr int canvas_height = window_height - 2 * inner_sep;
    constexpr auto x_scale = canvas_width / (point_max_x - point_min_x);
    constexpr auto y_scale = canvas_height / (point_max_y - point_min_y);

    return sf::Vector2f((p.x - point_min_x) * x_scale + inner_sep,
                        canvas_height + inner_sep -
                            (p.y - point_min_y) * y_scale);
  };

  if (window.isOpen()) {
    window.clear(sf::Color::Black);
    
    // Define and research font
    sf::Font font;
    if(!font.loadFromFile("georgia.ttf")){}
    
    // Choose what to write
    sf::Text textS;
    textS.setString("   Susceptible");        
    textS.setFont(font);
    textS.setCharacterSize(24);
    textS.setFillColor(sf::Color::Red);
    textS.setStyle(sf::Text::Bold);

    sf::Text textI;
    textI.setString("                         Infectious");        
    textI.setFont(font);
    textI.setCharacterSize(24);
    textI.setFillColor(sf::Color::Green);
    textI.setStyle(sf::Text::Bold);

    sf::Text textR;
    textR.setString("                                             Recovered");        
    textR.setFont(font);
    textR.setCharacterSize(24);
    textR.setFillColor(sf::Color::Blue);
    textR.setStyle(sf::Text::Bold);

    // Define the (0, 0) point drawn as a little white circle
    {
      constexpr auto radius = 5.f;
      constexpr auto outline_thickness = 2.f;
      sf::CircleShape zero{radius};
      zero.setFillColor(sf::Color::Black);
      zero.setOutlineThickness(outline_thickness);
      zero.setOutlineColor(sf::Color::White);
      zero.setOrigin(sf::Vector2f{radius, radius});
      zero.move(to_window_frame({0, 0}));
      window.draw(zero);
    }
    
    // Draw the points contained in the vectors
    for (auto const &p : pointsS) {
      constexpr auto radius = 5.f;
      sf::CircleShape c{radius};
      c.setFillColor(sf::Color::Red);
      c.setOrigin(sf::Vector2f{radius, radius});
      c.move(to_window_frame(p));
      window.draw(c);
    }

    for (auto const &p : pointsI) {
      constexpr auto radius = 5.f;
      sf::CircleShape c{radius};
      c.setFillColor(sf::Color::Green);
      c.setOrigin(sf::Vector2f{radius, radius});
      c.move(to_window_frame(p));
      window.draw(c);
    }

    for (auto const &p : pointsR) {
      constexpr auto radius = 5.f;
      sf::CircleShape c{radius};
      c.setFillColor(sf::Color::Blue);
      c.setOrigin(sf::Vector2f{radius, radius});
      c.move(to_window_frame(p));
      window.draw(c);
    }

    window.draw(textS);
    window.draw(textI);
    window.draw(textR);
    
    window.display();

    sf::Event event;
    while (window.waitEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        break;
      }
    }
  }
}
