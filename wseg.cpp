#include "wseg.hpp"
topit::WSeg::WSeg(p_t s, int l):
 IDraw(), start{s}, len{l}
{}

topit::p_t topit::WSeg::begin() const
{
  return start;
}

topit::p_t topit::WSeg::next(p_t prev) const
{
  if(prev==start)
  {
    if(len>1)
    {
      return {start.x,start.y+1};
    }
    return start;
  }
  int curent_index = prev.y - start.y;
  if(curent_index<len-1)
  {
    return {prev.x, prev.y+1};
  }
  return start;
}
