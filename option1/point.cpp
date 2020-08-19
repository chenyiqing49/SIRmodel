#include "point.hpp"

// overload dell'operatore ==
bool operator==(Point const& l, Point const& r)
{
  return l.x == r.x && l.y == r.y;
}

// overload dell'operatore !=
bool operator!=(Point const& l, Point const& r)
{
  return !(l == r);
}

