#ifndef SQUAER_HPP
#define SQUARE_HPP
#include "idraw.hpp"
namespace topit
{
  struct Square:IDraw {
    explicit Square(p_t p, int s);
    p_t begin() const override;
    p_t next(p_t prev) const override;
    private:
      p_t start;
      int side;
  };
}
#endif