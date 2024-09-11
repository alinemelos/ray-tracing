#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include "vector.h"
#include "point.h"
#include "ray.h"
#include <cmath>
using namespace std;

class Matrix{
    public:
        
        vector<vector<double>> elements;
        vector<vector<double>> elements_inverse;
        bool isInvertible;

        Matrix() : elements(4, vector<double>(4, 0)), elements_inverse(4, vector<double>(4, 0)), isInvertible(false) {}

        void create_inverse(){

            double det;
            double inv[4][4];

        
            inv[0][0] = elements[1][1]  * elements[2][2] * elements[3][3] - 
                    elements[1][1]  * elements[2][3] * elements[3][2] - 
                    elements[2][1]  * elements[1][2]  * elements[3][3] + 
                    elements[2][1]  * elements[1][3]  * elements[3][2] +
                    elements[3][1] * elements[1][2]  * elements[2][3] - 
                    elements[3][1] * elements[1][3]  * elements[2][2];

            inv[1][0] = -elements[1][0]  * elements[2][2] * elements[3][3] + 
                    elements[1][0]  * elements[2][3] * elements[3][2] + 
                    elements[2][0]  * elements[1][2]  * elements[3][3] - 
                    elements[2][0]  * elements[1][3]  * elements[3][2] - 
                    elements[3][0] * elements[1][2]  * elements[2][3] + 
                    elements[3][0] * elements[1][3]  * elements[2][2];

            inv[2][0] = elements[1][0]  * elements[2][1] * elements[3][3] - 
                    elements[1][0]  * elements[2][3] * elements[3][1] - 
                    elements[2][0]  * elements[1][1] * elements[3][3] + 
                    elements[2][0]  * elements[1][3] * elements[3][1] + 
                    elements[3][0] * elements[1][1] * elements[2][3] - 
                    elements[3][0] * elements[1][3] * elements[2][1];

            inv[3][0] = -elements[1][0]  * elements[2][1] * elements[3][2] + 
                    elements[1][0]  * elements[2][2] * elements[3][1] +
                    elements[2][0]  * elements[1][1] * elements[3][2] - 
                    elements[2][0]  * elements[1][2] * elements[3][1] - 
                    elements[3][0] * elements[1][1] * elements[2][2] + 
                    elements[3][0] * elements[1][2] * elements[2][1];

            inv[0][1] = -elements[0][1]  * elements[2][2] * elements[3][3] + 
                    elements[0][1]  * elements[2][3] * elements[3][2] + 
                    elements[2][1]  * elements[0][2] * elements[3][3] - 
                    elements[2][1]  * elements[0][3] * elements[3][2] - 
                    elements[3][1] * elements[0][2] * elements[2][3] + 
                    elements[3][1] * elements[0][3] * elements[2][2];

            inv[1][1] = elements[0][0]  * elements[2][2] * elements[3][3] - 
                    elements[0][0]  * elements[2][3] * elements[3][2] - 
                    elements[2][0]  * elements[0][2] * elements[3][3] + 
                    elements[2][0]  * elements[0][3] * elements[3][2] + 
                    elements[3][0] * elements[0][2] * elements[2][3] - 
                    elements[3][0] * elements[0][3] * elements[2][2];

            inv[2][1] = -elements[0][0]  * elements[2][1] * elements[3][3] + 
                    elements[0][0]  * elements[2][3] * elements[3][1] + 
                    elements[2][0]  * elements[0][1] * elements[3][3] - 
                    elements[2][0]  * elements[0][3] * elements[3][1] - 
                    elements[3][0] * elements[0][1] * elements[2][3] + 
                    elements[3][0] * elements[0][3] * elements[2][1];

            inv[3][1] = elements[0][0]  * elements[2][1] * elements[3][2] - 
                    elements[0][0]  * elements[2][2] * elements[3][1] - 
                    elements[2][0]  * elements[0][1] * elements[3][2] + 
                    elements[2][0]  * elements[0][2] * elements[3][1] + 
                    elements[3][0] * elements[0][1] * elements[2][2] - 
                    elements[3][0] * elements[0][2] * elements[2][1];

            inv[0][2] = elements[0][1]  * elements[1][2] * elements[3][3] - 
                    elements[0][1]  * elements[1][3] * elements[3][2] - 
                    elements[1][1]  * elements[0][2] * elements[3][3] + 
                    elements[1][1]  * elements[0][3] * elements[3][2] + 
                    elements[3][1] * elements[0][2] * elements[1][3] - 
                    elements[3][1] * elements[0][3] * elements[1][2];

            inv[1][2] = -elements[0][0]  * elements[1][2] * elements[3][3] + 
                    elements[0][0]  * elements[1][3] * elements[3][2] + 
                    elements[1][0]  * elements[0][2] * elements[3][3] - 
                    elements[1][0]  * elements[0][3] * elements[3][2] - 
                    elements[3][0] * elements[0][2] * elements[1][3] + 
                    elements[3][0] * elements[0][3] * elements[1][2];

            inv[2][2] = elements[0][0]  * elements[1][1] * elements[3][3] - 
                    elements[0][0]  * elements[1][3] * elements[3][1] - 
                    elements[1][0]  * elements[0][1] * elements[3][3] + 
                    elements[1][0]  * elements[0][3] * elements[3][1] + 
                    elements[3][0] * elements[0][1] * elements[1][3] - 
                    elements[3][0] * elements[0][3] * elements[1][1];

            inv[3][2] = -elements[0][0]  * elements[1][1] * elements[3][2] + 
                    elements[0][0]  * elements[1][2] * elements[3][1] + 
                    elements[1][0]  * elements[0][1] * elements[3][2] - 
                    elements[1][0]  * elements[0][2] * elements[3][1] - 
                    elements[3][0] * elements[0][1] * elements[1][2] + 
                    elements[3][0] * elements[0][2] * elements[1][1];

            inv[0][3] = -elements[0][1] * elements[1][2] * elements[2][3] + 
                    elements[0][1] * elements[1][3] * elements[2][2] + 
                    elements[1][1] * elements[0][2] * elements[2][3] - 
                    elements[1][1] * elements[0][3] * elements[2][2] - 
                    elements[2][1] * elements[0][2] * elements[1][3] + 
                    elements[2][1] * elements[0][3] * elements[1][2];

            inv[1][3] = elements[0][0] * elements[1][2] * elements[2][3] - 
                    elements[0][0] * elements[1][3] * elements[2][2] - 
                    elements[1][0] * elements[0][2] * elements[2][3] + 
                    elements[1][0] * elements[0][3] * elements[2][2] + 
                    elements[2][0] * elements[0][2] * elements[1][3] - 
                    elements[2][0] * elements[0][3] * elements[1][2];

            inv[2][3] = -elements[0][0] * elements[1][1] * elements[2][3] + 
                    elements[0][0] * elements[1][3] * elements[2][1] + 
                    elements[1][0] * elements[0][1] * elements[2][3] - 
                    elements[1][0] * elements[0][3] * elements[2][1] - 
                    elements[2][0] * elements[0][1] * elements[1][3] + 
                    elements[2][0] * elements[0][3] * elements[1][1];

            inv[3][3] = elements[0][0] * elements[1][1] * elements[2][2] - 
                    elements[0][0] * elements[1][2] * elements[2][1] - 
                    elements[1][0] * elements[0][1] * elements[2][2] + 
                    elements[1][0] * elements[0][2] * elements[2][1] + 
                    elements[2][0] * elements[0][1] * elements[1][2] - 
                    elements[2][0] * elements[0][2] * elements[1][1];

            det = elements[0][0] * inv[0][0] + elements[0][1] * inv[1][0] + elements[0][2] * inv[2][0] + elements[0][3] * inv[3][0];

            if (det == 0){
                isInvertible = false;

            }else{
                isInvertible = true;

                det = 1.0 / det;

                for (int i = 0; i < 4; i++){
                    for(int j = 0; j < 4; j++){
                        elements_inverse[i][j] = inv[i][j] * det;
                    }  
                }
            }

        }

        ray transform_ray(const ray &r){
            double x, y, z;
            x = r.origin().x*elements_inverse[0][0] + r.origin().y*elements_inverse[0][1] + r.origin().z*elements_inverse[0][2] + elements_inverse[0][3];
            y = r.origin().x*elements_inverse[1][0] + r.origin().y*elements_inverse[1][1] + r.origin().z*elements_inverse[1][2] + elements_inverse[1][3];
            z = r.origin().x*elements_inverse[2][0] + r.origin().y*elements_inverse[2][1] + r.origin().z*elements_inverse[2][2] + elements_inverse[2][3];
            Point origin = Point(x, y, z);

            x = r.direction().x*elements_inverse[0][0] + r.direction().y*elements_inverse[0][1] + r.direction().z*elements_inverse[0][2];
            y = r.direction().x*elements_inverse[1][0] + r.direction().y*elements_inverse[1][1] + r.direction().z*elements_inverse[1][2];
            z = r.direction().x*elements_inverse[2][0] + r.direction().y*elements_inverse[2][1] + r.direction().z*elements_inverse[2][2];
            Vector direction = Vector(x, y, z);
            
            return ray(origin, direction);
        }

        Point transform_point(const Point &k){
            double x, y, z;
            x = k.x*elements[0][0] + k.y*elements[0][1] + k.z*elements[0][2] + elements[0][3];
            y = k.x*elements[1][0] + k.y*elements[1][1] + k.z*elements[1][2] + elements[1][3];
            z = k.x*elements[2][0] + k.y*elements[2][1] + k.z*elements[2][2] + elements[2][3];
            Point p =  Point(x, y, z);
            return p;
        }

        Vector transform_vector(const Vector &k){
            double x, y, z;
            x = k.x*elements[0][0] + k.y*elements[0][1] + k.z*elements[0][2];
            y = k.x*elements[1][0] + k.y*elements[1][1] + k.z*elements[1][2];
            z = k.x*elements[2][0] + k.y*elements[2][1] + k.z*elements[2][2];
            Vector v =  Vector(x, y, z);
            return v;
        }

        vector<vector<double>> initialize(string eixo, double ang){
                ang = ang*3.14159292004/180;
                if(eixo == "x"){
                         vector<vector<double>> rotate{
                               {1, 0, 0, 0},
                               {0, cos(ang), -sin(ang), 0},
                               {0, sin(ang), cos(ang), 0},
                               {0, 0, 0, 1} 
                        };
                        return rotate;

                }else if(eixo == "y"){
                        vector<vector<double>> rotate{
                               {cos(ang), 0, sin(ang), 0},
                               {0, 1, 0, 0},
                               {-sin(ang),0 , cos(ang), 0},
                               {0, 0, 0, 1} 
                        };
                        return rotate;

                }else if(eixo == "z"){
                        vector<vector<double>> rotate{
                               {cos(ang), -sin(ang), 0, 0},
                               {sin(ang), cos(ang), 0, 0},
                               {0, 0, 1, 0},
                               {0, 0, 0, 1} 
                        };
                        return rotate;
                }
        }

};


    

