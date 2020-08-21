#include "point.hpp"

// overload of the == operator
bool operator==(Point const& l, Point const& r)
{
  return l.x == r.x && l.y == r.y;
}

// overload of the != operator
bool operator!=(Point const& l, Point const& r)
{
  return !(l == r);
}
