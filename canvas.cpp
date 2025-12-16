#include "canvas.hpp"
#include <iostream>
char * topit::canvas(f_t fr, char fill)
{
  size_t s = rows(fr) * cols(fr);
  char * c = new char[s];
  for(size_t i=0; i<s; ++i)
  {
    c[i] = fill;
  }
  return c;
}

void topit::paint(p_t p, char * cnv, f_t fr, char fill)
{
  size_t dx = p.x-fr.aa.x;
  size_t dy = fr.bb.y-p.y;
  cnv[dy*cols(fr)+dx] = fill;
}

void topit::flush(std::ostream & os, const char * cnv, f_t fr)
{
  for(size_t i=0; i<rows(fr); ++i)
  {
    for(size_t j=0; j<cols(fr); ++j)
    {
      os << cnv[i * cols(fr) + j];
    }
    os << "\n";
  }
}
topit::Layers::Layers():
 points_{0}, pts_{nullptr}, layers_{0}, sizes_{nullptr}
{}

topit::Layers::~Layers()
{
  delete[] pts_;
  delete[] sizes_;
}

void topit::Layers::append(const IDraw & dr)
{
  size_t *ext_sizes = new size_t[layers_+1];
  try
  {
    topit::append(&dr, &pts_, points_);
  }
  catch(...)
  {
    delete[] ext_sizes;
    throw;
  }
  for(size_t i=0;i<layers_; ++i)
  {
    ext_sizes[i]=sizes_[i];
  }
  ext_sizes[layers_]=points_;
  delete[] sizes_;
  sizes_= ext_sizes;
  ++layers_;
}

topit::Layers::Layers(const Layers& other):
  points_{other.points_},
  pts_{nullptr},
  layers_{other.layers_},
  sizes_{nullptr}
{
  if (points_ > 0)
  {
    pts_ = new p_t[points_];
    for (size_t i = 0; i < points_; ++i)
    {
      pts_[i] = other.pts_[i];
    }
  }
  if (layers_ > 0)
  {
    sizes_ = new size_t[layers_];
    for (size_t i = 0; i < layers_; ++i)
    {
      sizes_[i] = other.sizes_[i];
    }
  }
}

topit::Layers& topit::Layers::operator=(const Layers& other)
{
  if (this == &other)
  {
    return *this;
  }
  p_t* newPts = nullptr;
  size_t* newSizes = nullptr;

  if (other.points_ > 0) {
    newPts = new p_t[other.points_];
    for (size_t i = 0; i < other.points_; ++i)
    {
      newPts[i] = other.pts_[i];
    }
  }
  if (other.layers_ > 0)
  {
    newSizes = new size_t[other.layers_];
    for (size_t i = 0; i < other.layers_; ++i)
    {
      newSizes[i] = other.sizes_[i];
    }
  }

  delete [] pts_;
  delete [] sizes_;

  pts_ = newPts;
  sizes_ = newSizes;
  points_ = other.points_;
  layers_ = other.layers_;

  return *this;
}

topit::Layers::Layers(Layers&& other) noexcept:
  points_{other.points_},
  pts_{other.pts_},
  layers_{other.layers_},
  sizes_{other.sizes_}
{
  other.points_ = 0;
  other.layers_ = 0;
  other.pts_ = nullptr;
  other.sizes_ = nullptr;
}

topit::Layers& topit::Layers::operator=(Layers&& other) noexcept
{
  if (this == &other) {
    return *this;
  }

  delete [] pts_;
  delete [] sizes_;

  pts_ = other.pts_;
  sizes_ = other.sizes_;
  points_ = other.points_;
  layers_ = other.layers_;

  other.pts_ = nullptr;
  other.sizes_ = nullptr;
  other.points_ = 0;
  other.layers_ = 0;

  return *this;
}