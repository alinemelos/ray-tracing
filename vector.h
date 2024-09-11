#ifndef VECTORH
#define VECTORH

#include <bits/stdc++.h>
#include <iostream>

//classe do vetor
class Vector{
        public:
           double x, y, z;

            Vector(double x, double y, double z) : x(x), y(y), z(z) {}

            Vector(){
                x = 0;
                y = 0;
                z = 0;
            }   
            
            double norm(){
                double norm = sqrt(x*x + y*y + z*z);
                return norm;
            }

            double dot(double a, double b, double c){
                return x*a + y*b + z*c;
            }

/*            Vector cross(double a, double b, double c){
                return Vector(y*c - z*b, z*a - x*c, x*b - y*a);
            }
*/
            void make_unit_vector(){
                double norma = norm();
                if(norma == 0){
                    x = 0;
                    y = 0;
                    z = 0;
                }else{
                    x = x/norma;
                    y = y/norma;
                    z = z/norma;
                }
            }

            void print(){
                std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
            }
};

//overload das operações com vetor

Vector operator+(const Vector& v1, const Vector& v2){
    return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector operator-(const Vector& v1, const Vector& v2){
    return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector operator*(const Vector& v1, const Vector& v2){
    return Vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector operator*(const Vector& v, double n){
    return Vector(v.x * n, v.y * n, v.z * n);
}

Vector operator/(const Vector& v1, const Vector& v2){
    return Vector(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

Vector operator/(const Vector& v, double n){
    return Vector(v.x / n, v.y / n, v.z / n);
}

Vector operator%(const Vector& v1, const Vector& v2){
    return Vector(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

#endif