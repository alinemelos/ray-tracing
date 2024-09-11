#ifndef SPHEREH
#define SPHEREH

#include <math.h>
#include "vector.h"
#include "point.h"
#include "objects.h"
#include "ray.h"
using namespace std;
#define Not_intersect -1
#define Discard 1e-6

class Sphere: public Object {
public:
    Sphere(Point center, double radius, Vector color, double kd, double ks, double ka, double kr, double kt, double nrugo, double ior) 
        : center(center), radius(radius), Object(color, kd, ks, ka, kr, kt, nrugo, ior) {}

    double intersect(const ray &r) override {
        double distance;
        Vector oc = center - r.origin();
        double A = r.direction().dot(r.direction().x, r.direction().y, r.direction().z);
        double B = -2*r.direction().dot(oc.x, oc.y, oc.z);
        double C = oc.dot(oc.x, oc.y, oc.z) - pow(radius, 2);

        double Delta = pow(B, 2) - 4*A*C;

        if(Delta >= 0){
            double distance1 = (-B+sqrt(Delta)) /  2*A;
            double distance2 = (-B-sqrt(Delta)) /  2*A;
            distance = distance1;

            if(distance1 < Discard){
                if(distance2 < Discard){
                    return Not_intersect;
                }
                distance = distance2;
            }

            if(distance1 > Discard && distance2 > Discard){distance = min(distance1, distance2);}

            return distance;
        }
        return Not_intersect;
    }

    Vector returnNormal(const ray& r, double t) override {
        Point intersection_point = r.at(t);
        Vector outward_normal = intersection_point - center;
        return outward_normal;
    }

    Point center;
    double radius;
};

#endif