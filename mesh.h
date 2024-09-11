#ifndef MESHH
#define MESHH

#include <math.h>
#include <cmath>
#include "vector.h"
#include "point.h"
#include "ray.h"
#include "plane.h"
#include "objects.h"
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define Not_intersect -1
#define Discard 1e-6

class Triangle{
    public:

        Triangle(Point A, Point B, Point C){

            this->A = A;
            this->B = B;
            this->C = C;
        }

        Point A;
        Point B;
        Point C;


        double Area(Point X, Point Y, Point Z){
            Vector side1 = Y - X;
            Vector side2 = Z - X;
            double area = (side1%side2).norm()/2;
            return area;
        }


        double intersect(const ray& r){
            Vector normal = (B - A) % (C - A);
            Plane plane = Plane(A, normal, Vector(0, 0, 0), 0, 0, 0, 0, 0, 0, 0); // Valores dummy para kd, ks, etc.
            double distance = plane.intersect(r);
            if(distance == 0){return 0;}
            Point P = r.at(distance);

            double alpha = Area(P, B, C) / Area(A, B, C);
            double beta = Area(P, A, C) / Area(A, B, C);
            double gama = Area(P, A, B) / Area(A, B, C);

            //cout << "Alfa: " << alpha << " Beta: " << beta << " Gama: " << gama << endl;
           //cout << "Alfa + Beta + Gama: " << alpha + beta + gama << endl;
            //bool verificar = (alpha + beta + gama) <= 1;
            //cout << "(Alfa + Beta + Gama) <= 1: " << verificar << endl;

            bool hit = (alpha >= 0) && (beta >= 0) && (gama >= 0) && (fabs(alpha + beta + gama - 1) < 1e-6);
            //bool hit = (alpha >= 0) && (beta >= 0) && (gama >= 0) && ((alpha + beta + gama) <= 1);

            if(hit && distance > Discard){return distance;}
            return Not_intersect;

        }

};


class Mesh: public Object{
    public:
        double nTriangles; 
        double nVertex;
        vector<Point> Vertices;
        vector<vector<int>> triplas;
        Vector color;
        vector <Triangle> Triangles;


        Mesh(int nTriangles, int nVertex, vector<Point> Vertices, vector<vector<int>> triplas, Vector color, double kd, double ks, double ka, double kr, double kt, double nrugo, double ior)
        : nTriangles(nTriangles), nVertex(nVertex), Vertices(Vertices), triplas(triplas), Object(color, kd, ks, ka, kr, kt, nrugo, ior) {
            for(int i=0; i<nTriangles; i++){
                Point A = Vertices[triplas[i][0]];
                Point B = Vertices[triplas[i][1]];
                Point C = Vertices[triplas[i][2]];
                Triangle tri = Triangle(A, B, C);
                Triangles.push_back(tri);
            }
        }

        double intersect(const ray& r) override {
            double dist;
            double menor_dist = INT_FAST16_MAX;
            for(Triangle tri : Triangles){
                dist = tri.intersect(r);
                if(dist < menor_dist && dist > 0){menor_dist = dist;}
            }
            if(menor_dist == INT_FAST16_MAX){return 0;}
            return menor_dist;
        }

        // percorre todos os triangulos e verifica qual foi atingido
        
        Vector returnNormal(const ray& r, double t) override {
            for (Triangle tri : Triangles) {
                double distance = tri.intersect(r);
                if (distance > 0 && distance == t) {
                    Vector normal = (tri.B - tri.A) % (tri.C - tri.A);
                    
                    // inverte a direção da normal se ela for igual a direção do raio
                    if(r.direction().dot(normal.x, normal.y, normal.z) > 0){normal = normal*(-1);}

                    normal.make_unit_vector();
                    // retorna a normal desse triangulo na posição de interseção
                    return normal;
                }
            }
            return Vector(0, 0, 0); // Return zero vector if no intersection found
        }

};
#endif