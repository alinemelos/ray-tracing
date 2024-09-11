#ifndef CAMH
#define CAMH

#include <bits/stdc++.h>
#include <iostream>
#include "vector.h"
#include "point.h"

class CAM{
    public:
        CAM(Point origin, Point target, Vector up, Vector cor, double height, double length, double distance, Vector ambient_light){
            this->origin = origin;
            this->target = target;
            this->up = up;
            this->cor = cor;
            this->distance = distance;
            this->height = height;
            this->length = length;
            this->ambient_light = ambient_light;
            W = target - origin; //z
            U = W % up; //y
            V = U % W; // x
            W.make_unit_vector();
            U.make_unit_vector();
            V.make_unit_vector();
        }

        Point origin;
        Point target;
        Vector up;
        Vector W;
        Vector V;
        Vector U;
        Vector cor;
        double distance;
        double height;
        double length;
        Vector ambient_light;

};

#endif