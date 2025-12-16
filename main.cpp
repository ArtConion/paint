#include <iostream>
#include "ascii_draw.hpp"
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
  struct Square:IDraw {
    explicit Square(p_t p, int s);
    p_t begin() const override;
    p_t next(p_t prev) const override;
    private:
      p_t start;
      int side;
  };
}
int main()
{
  using namespace topit;
  int err = 0;
  IDraw *shp[3] = {};
  Layers layers;
  try
  {
    shp[0] = new Dot({-5,-5});
    shp[1] = new Dot({10,10});
    shp[2] = new Dot({-1,1});

    for(size_t i=0; i<6; ++i)
    {
      layers.append(*(shp[i]));
    }
    f_t fr = layers.frame();
    char * cnv = canvas(fr, '.');
    const char * brush = "#*%";
    for(size_t k=0; k<layers.layers(); ++k)
    {
      size_t start = layers.start(k);
      size_t end = layers.end(k);
      for(size_t i=start; k<end; ++i)
      {
        paint(layers.point(i), cnv, fr, brush[k]);
      }
    }
    flush(std::cout, cnv, fr);
    delete[] cnv;
  }
  catch(...)
  {
    std::cerr << "Error\n";
    err = 1;
  }

  delete shp[0];
  delete shp[1];
  delete shp[2];
  delete shp[3];
  delete shp[4];
  delete shp[5];
  return err;
}

// Точка

// Вертикальная линия

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

// Квадрат

topit::Square::Square(p_t p, int s):
 IDraw(), start{p}, side{s}
{
  if(side <= 0)
  {
    throw std::invalid_argument("Invalid square side");
  }
}

topit::p_t topit::Square::begin() const
{
  return start;
}

topit::p_t topit::Square::next(p_t prev) const
{
  if (prev.x < start.x || prev.x >= start.x + side || prev.y < start.y || prev.y >= start.y + side)
  {
    throw std::logic_error("bad prev");
  }

  if (prev.x == start.x + side - 1 && prev.y == start.y + side - 1)
  {
    return start;
  }

  if (prev.x < start.x + side - 1)
  {
    return p_t{prev.x + 1, prev.y};
  } else
  {
    return p_t{start.x, prev.y + 1};
  }
}

// Прямоугольник

// Заполненный прямоугольник
