#include "idraw.hpp"
namespace
{
  topit::p_t * extend(const topit::p_t * pts, size_t s, topit::p_t fill)
  {
    topit::p_t * res = new topit::p_t[s+1];
    for(size_t i=0; i<s; ++i)
    {
      res[i] = pts[i];
    }
    res[s] = fill;
    return res;
  }

  void extend(topit::p_t ** pts, size_t & s, topit::p_t fill)
  {
    topit::p_t * res = extend(*pts, s, fill);
    delete[] *pts;
    ++s;
    *pts = res;
  }
}

void topit::append(const IDraw * sh, p_t ** ppts, size_t & s)
{
  extend(ppts, s, sh->begin());
  p_t b = sh->begin();
  while(sh->next(b) != sh->begin())
  {
    b = sh->next(b);
    extend(ppts, s, b);
  }
}
