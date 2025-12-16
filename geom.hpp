#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>
namespace topit
{
  struct p_t
  {
    int x,y;
  };
  struct f_t
  {
    p_t aa, bb;
  };
  size_t rows(f_t fr);
  size_t cols(f_t fr);
  bool operator==(p_t a, p_t b);
  bool operator!=(p_t a, p_t b);
  f_t frame(const p_t * pts, size_t s);
}
#endif