#include "point.hpp"

bool operator==(Point const& l, Point const& r)
{
  return l.x == r.x && l.y == r.y;
}

bool operator!=(Point const& l, Point const& r)
{
  return !(l == r);
}

