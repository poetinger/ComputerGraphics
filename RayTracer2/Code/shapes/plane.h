#ifndef PLANE_H_
#define PLANE_H_

#include "../object.h"

class Plane : public Object {
public:
  Plane(Point const &point, Vector const N);

  virtual Hit intersect(Ray const &ray);
  virtual TextureCoordinates textureCoordinates(Point const &point);

  Point const point;
  Vector const N;
};

#endif
