#ifndef CANVAS_HPP
#define CANVAS_HPP
#include <iosfwd>
#include "idraw.hpp"
namespace topit
{
  char * canvas(f_t fr, char fill);
  void paint(p_t p, char * cnv, f_t fr, char fill);
  void flush(std::ostream & os, const char * cnv, f_t fr);
  struct Layers {
    Layers();
    ~Layers();
    Layers(const Layers& other);
    Layers& operator=(const Layers& other);
    Layers(Layers&& other) noexcept;
    Layers& operator=(Layers&& other) noexcept;

    void append(const IDraw & dr);
    f_t frame() const
    {
      return topit::frame(pts_, points_);
    }
    size_t points() const
    {
      return points_;
    }
    size_t layers() const
    {
      return layers_;
    }
    size_t start(size_t i) const
    {
      return !i ? 0 : sizes_[i-1];
    }
    size_t end(size_t i) const
    {
      return sizes_[i];
    }
    p_t point(size_t i) const
    {
      return pts_[i];
    }
    private:
      size_t points_;
      p_t * pts_;
      size_t layers_;
      size_t * sizes_;
  };
}

#endif