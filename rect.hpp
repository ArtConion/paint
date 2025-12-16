#ifndef RECT_HPP
#define RECT_HPP
#include "idraw.hpp"
namespace topit
{
  struct Rect:IDraw {
    Rect(p_t pos, int w, int h);
    Rect(p_t a, p_t b);
    p_t begin() const override;
    p_t next(p_t prev) const override;
    private:
     f_t rect;
  };
} 
#endif