#ifndef RAY_H
#define RAY_H

#include "vector.h"
#include "point.h"

class ray {
  public:
    ray() {}

    ray(const Point& origin, const Vector& direction) : orig(origin), dir(direction) {
      dir.make_unit_vector();
    }

    Point origin() const { return orig; }
    Vector direction() const { return dir; }

 Point at(double t) const {
        return orig + dir*t;
    }

  private:
 Point orig;
    Vector dir;
};

#endif
