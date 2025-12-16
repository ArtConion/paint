#ifndef FRECT_HPP
#define FRECR_HPP
#include "idraw.hpp"
namespace topit
{
  struct FRect:IDraw 
  {
    FRect(p_t pos, int w, int h);
    FRect(p_t a, p_t b);
    p_t begin() const override;
    p_t next(p_t prev) const override;
    f_t frect;
  };
} 
#endif