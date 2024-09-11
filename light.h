#ifndef LIGHT_H
#define LIGHT_H

#include "point.h"   
#include "vector.h"  

class Light {
    public:
        Point origin;
        Vector intensity; //ILn=light intensity
        //Vector ambient_colour; Ia=ambient colour
        
        Light(const Point& origin, const Vector& intensity)
            : origin(origin), intensity(intensity){}
        
        void print(){
            std::cout << "Light origin: ";
            origin.print();
            std::cout << "Light intensity: ";
            intensity.print();
        }
};

#endif // LIGHT_H
