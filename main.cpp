#include <iostream>
namespace topit {
   struct p_t{
    int x,y;
  };
  struct f_t{
    p_t aa, bb;
  };
  size_t rows(f_t fr);
  size_t cols(f_t fr);
  bool operator==(p_t a, p_t b);
  bool operator!=(p_t a, p_t b);
  struct IDraw {
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t prev) const =  0;
  };
  struct Dot:IDraw {
    explicit Dot(p_t dd);
    p_t begin() const override;
    p_t next(p_t prev) const override;
    private:
      p_t d;
  };
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
  struct Rect:IDraw {
    Rect(p_t pos, int w, int h);
    Rect(p_t a, p_t b);
    p_t begin() const override;
    p_t next(p_t prev) const override;
    private:
     f_t rect;
  };
  struct FRect:IDraw {
    FRect(p_t pos, int w, int h);
    FRect(p_t a, p_t b);
    p_t begin() const override;
    p_t next(p_t prev) const override;
    f_t frect;
  };
  p_t * extend(const p_t * pts, size_t s, p_t fill);
  void extend(p_t ** pts, size_t & s, p_t fill);
  void append(const IDraw * sh, p_t ** ppts, size_t & s);
  f_t frame(const p_t * pts, size_t s);
  char * canvas(f_t fr, char fill);
  void paint(p_t p, char * cnv, f_t fr, char fill);
  void flush(std::ostream & os, const char * cnv, f_t fr);

  struct Layers {
    Layers();
    ~Layers();
    Layers(const Layers& other);
    Layers& operator=(const Layers& other);
    Layers(Layers&& other);
    Layers& operator=(Layers&& other);

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
topit::p_t * topit::extend(const p_t * pts, size_t s, p_t fill)
{
  p_t * res = new p_t[s+1];
  for(size_t i=0; i<s; ++i)
  {
    res[i] = pts[i];
  }
  res[s] = fill;
  return res;
}

void topit::extend(p_t ** pts, size_t & s, p_t fill)
{
  p_t * res = extend(*pts, s, fill);
  delete[] *pts;
  ++s;
  *pts = res;
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

topit::f_t topit::frame(const p_t * pts, size_t s)
{
  int minx = pts[0].x;
  int miny = pts[0].y;
  int maxx = pts[0].x;
  int maxy = pts[0].y;
  for(size_t i=0; i<s; ++i)
  {
    minx = std::min(minx,pts[i].x);
    miny = std::min(miny,pts[i].y);
    maxx = std::max(maxx,pts[i].x);
    maxy = std::max(maxy,pts[i].y);
  }
  p_t a{minx, miny};
  p_t b{maxx, maxy};
  return f_t{a, b};
}

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

size_t topit::rows(f_t fr)
{
  return (fr.bb.y-fr.aa.y+1);
}

size_t topit::cols(f_t fr)
{
  return (fr.bb.x-fr.aa.x+1);
}

bool topit::operator==(p_t a, p_t b)
{
  return a.x==b.x && a.y==b.y;
}

bool topit::operator!=(p_t a, p_t b)
{
  return !(a==b);
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
  if (points_ > 0) {
    pts_ = new p_t[points_];
    for (size_t i = 0; i < points_; ++i) {
      pts_[i] = other.pts_[i];
    }
  }
  if (layers_ > 0) {
    sizes_ = new size_t[layers_];
    for (size_t i = 0; i < layers_; ++i) {
      sizes_[i] = other.sizes_[i];
    }
  }
}

topit::Layers& topit::Layers::operator=(const Layers& other)
{
  if (this == &other) {
    return *this;
  }
  p_t* newPts = nullptr;
  size_t* newSizes = nullptr;

  if (other.points_ > 0) {
    newPts = new p_t[other.points_];
    for (size_t i = 0; i < other.points_; ++i) {
      newPts[i] = other.pts_[i];
    }
  }
  if (other.layers_ > 0) {
    newSizes = new size_t[other.layers_];
    for (size_t i = 0; i < other.layers_; ++i) {
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

topit::Layers::Layers(Layers&& other):
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

topit::Layers& topit::Layers::operator=(Layers&& other)
{
  if (this == &other) {
    return *this;
  }
  p_t* newPts = nullptr;
  size_t* newSizes = nullptr;

  if (other.points_ > 0) {
    newPts = new p_t[other.points_];
    for (size_t i = 0; i < other.points_; ++i) {
      newPts[i] = other.pts_[i];
    }
  }
  if (other.layers_ > 0) {
    newSizes = new size_t[other.layers_];
    for (size_t i = 0; i < other.layers_; ++i) {
      newSizes[i] = other.sizes_[i];
    }
  }
}
// Точка

topit::Dot::Dot(p_t dd):
 IDraw(), d{dd}
{}

topit::p_t topit::Dot::begin() const
{
  return d;
}

topit::p_t topit::Dot::next(p_t prev) const
{
  if (prev != d)
  {
    throw std::logic_error("bad prev");
  }
  return d;
}

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

topit::Rect::Rect(p_t pos, int w, int h):
 IDraw(), rect{pos, {pos.x+w, pos.y+h}}
{
  if(!(w>0 && h>0))
  {
    throw std::logic_error("bad rect");
  }
}

topit::Rect::Rect(p_t a, p_t b):
 Rect(a, b.x-a.x, b.y-a.y)
{}

topit::p_t topit::Rect::begin() const
{
  return rect.aa;
}
topit::p_t topit::Rect::next(p_t prev) const
{
  if(prev.x == rect.aa.x && prev.y < rect.bb.y)
  {
    return {prev.x, prev.y+1};
  }
  else if(prev.y == rect.bb.y && prev.x < rect.bb.x)
  {
    return {prev.x+1, prev.y};
  }
  else if (prev.x == rect.bb.x && prev.y >rect.aa.y)
  {
    return {prev.x, prev.y-1};
  }
  else if(prev.y == rect.aa.y && prev.x > rect.aa.x)
  {
    return {prev.x-1, prev.y};
  }
  throw std::logic_error("bad prev");
}

// Заполненный прямоугольник

topit::FRect::FRect(p_t pos, int w, int h):
 IDraw(), frect{pos, {pos.x+w,pos.y+h}}
{
  if(!(w>0 && h>0))
  {
    throw std::logic_error("bad frect");
  }
}
topit::FRect::FRect(p_t a, p_t b):
 FRect(a, b.x-a.x, b.y-a.y)
{}

topit::p_t topit::FRect::begin() const
{
  return frect.aa;
}

topit::p_t topit::FRect::next(p_t prev) const
{
  if(prev.x < frect.bb.x)
  {
    return {prev.x+1, prev.y};
  }
  else if(prev.x == frect.bb.x && prev.y < frect.bb.y)
  {
    return {frect.aa.x, prev.y+1};
  }
  else if(prev == frect.bb)
  {
    return frect.aa;
  }
  throw std::logic_error("bad prev");
}