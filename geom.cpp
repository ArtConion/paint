#include "geom.hpp"
#include <algorithm>
size_t topit::rows(f_t fr)
{
  return (fr.bb.y-fr.aa.y+1);
}

size_t topit::cols(f_t fr)
{
  return (fr.bb.x-fr.aa.x+1);
}

bool topit::operator==(p_t a, p_t b)
{
  return a.x==b.x && a.y==b.y;
}

bool topit::operator!=(p_t a, p_t b)
{
  return !(a==b);
}

topit::f_t topit::frame(const p_t * pts, size_t s)
{
  int minx = pts[0].x;
  int miny = pts[0].y;
  int maxx = pts[0].x;
  int maxy = pts[0].y;
  for(size_t i=0; i<s; ++i)
  {
    minx = std::min(minx,pts[i].x);
    miny = std::min(miny,pts[i].y);
    maxx = std::max(maxx,pts[i].x);
    maxy = std::max(maxy,pts[i].y);
  }
  p_t a{minx, miny};
  p_t b{maxx, maxy};
  return f_t{a, b};
}