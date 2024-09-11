#ifndef OBJECT
#define OBJECT
#include "ray.h"
#include "vector.h"

class Object {
public:
    Vector color;
    double kd, ks, ka, kr, kt, nrugo, ior;

    Object(Vector color, double kd, double ks, double ka, double kr, double kt, double nrugo, double ior)
        : color(color), kd(kd), ks(ks), ka(ka), kr(kr), kt(kt), nrugo(nrugo), ior(ior) {}

    virtual ~Object() = default;

    virtual double intersect(const ray &r) = 0;
    virtual Vector returnNormal(const ray& r, double t) = 0;
};

#endif
