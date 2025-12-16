#include "frect.hpp"
#include <stdexcept>
topit::FRect::FRect(p_t pos, int w, int h):
 IDraw(), frect{pos, {pos.x+w,pos.y+h}}
{
  if(!(w>0 && h>0))
  {
    throw std::logic_error("bad frect");
  }
}
topit::FRect::FRect(p_t a, p_t b):
 FRect(a, b.x-a.x, b.y-a.y)
{}

topit::p_t topit::FRect::begin() const
{
  return frect.aa;
}

topit::p_t topit::FRect::next(p_t prev) const
{
  if(prev.x < frect.bb.x)
  {
    return {prev.x+1, prev.y};
  }
  else if(prev.x == frect.bb.x && prev.y < frect.bb.y)
  {
    return {frect.aa.x, prev.y+1};
  }
  else if(prev == frect.bb)
  {
    return frect.aa;
  }
  throw std::logic_error("bad prev");
}