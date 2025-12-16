#include <iostream>
#include "ascii_draw.hpp"
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
