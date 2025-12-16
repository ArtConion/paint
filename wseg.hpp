#ifndef WSEG_HPP
#define WSEG_HPP
#include "idraw.hpp"
namespace topit
{
  struct WSeg:IDraw {
    explicit WSeg(p_t s, int l);
    p_t begin() const override;
    p_t next(p_t prev) const override;
    private:
      p_t start;
      int len;
  };   
}
#endif