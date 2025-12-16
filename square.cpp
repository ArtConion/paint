#include <stdexcept>
#include "square.hpp"
topit::Square::Square(p_t p, int s):
 IDraw(), start{p}, side{s}
{
  if(side <= 0)
  {
    throw std::invalid_argument("Invalid square side");
  }
}

topit::p_t topit::Square::begin() const
{
  return start;
}

topit::p_t topit::Square::next(p_t prev) const
{
  if (prev.x < start.x || prev.x >= start.x + side || prev.y < start.y || prev.y >= start.y + side)
  {
    throw std::logic_error("bad prev");
  }

  if (prev.x == start.x + side - 1 && prev.y == start.y + side - 1)
  {
    return start;
  }

  if (prev.x < start.x + side - 1)
  {
    return p_t{prev.x + 1, prev.y};
  } else
  {
    return p_t{start.x, prev.y + 1};
  }
}
