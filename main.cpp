#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "vector.h"
#include "point.h"
#include "cam.h"
#include "objects.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "mesh.h"
#include "matrix.h"
#include "light.h"
#include "cylinder.h"
using namespace std;
#define Not_intersect -1
#define Discard 1e-6

Vector Render(const CAM &cam, const vector<Object*> &Objects, const ray &raio, const vector<Light> &Lights, int recursao);
Vector Phong(CAM cam, Object* Objectt, ray raio, double t, vector<Light> Lights, vector<Object*> Recursao, int recursao);

//Organiza a lista do menor pro maior, mas se for 0, ele coloca no final da lista
bool return_min_dist(const pair<double, Object*> &dist1, const pair<double, Object*> &dist2){
    if(dist1.first == 0){return false;}
    if(dist2.first == 0){return true;}
    return dist1.first < dist2.first;

}


double dt (Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

Vector refracted (Vector& view, Vector& normal, double ior){
    double cosi = normal.dot(view.x, view.y, view.z);
    Vector n2 = normal;
    double ior2 = ior;
    if (cosi < 0.0){
        n2= n2*(-1);
        ior2 = 1.0/ior2;
        cosi *= -1;
    }
    double delta = 1.0 - (1.0 - cosi * cosi) / (ior2 * ior2);
    if (delta < 0.0) {
        throw -1;
    }
    return view / (-ior2) - n2 * (sqrt(delta) - cosi / ior2);

}

Vector Phong(CAM cam, Object* Objectt, ray raio, double t, vector<Light> Lights, vector<Object*> Recursao, int recursao){

    double ka, ks, kd, kr, kt, nrugo, espec, difuse, n_transm;
    Point Colisao;
    Vector ambient_light, Od, normal, IL, L, R, V, Difusa, Especular, I, Refletido, Transmitido;

    ambient_light = cam.ambient_light/255;
    
    ka = Objectt->ka;
    ks = Objectt->ks;
    kd = Objectt->kd;
    kr = Objectt->kr;
    kt = Objectt->kt;
    nrugo = Objectt->nrugo;

    Od = Objectt->color/255;

    normal = Objectt->returnNormal(raio, t);
    normal.make_unit_vector();

    I = ambient_light*ka*Od;    


    for(Light& light: Lights){
        IL = light.intensity/255;
        Colisao = raio.at(t);

        L = light.origin - Colisao;
        L.make_unit_vector();
        
        R = (normal*2)*(L.dot(normal.x, normal.y, normal.z)) - L;
        R.make_unit_vector();

        V = cam.origin - Colisao;
        V.make_unit_vector();

        difuse = normal.dot(L.x, L.y, L.z);
        if (difuse > 0) {
            I = I + IL*Od*kd*difuse;
        }

        espec = R.dot(V.x, V.y, V.z);
        if (espec > 0) {
            I = I + IL*ks*pow(espec, nrugo);
        }

        if(recursao < 3 && dt(raio.origin(), raio.at(t)) > Discard){
            Refletido = (normal*2)*(V.dot(normal.x, normal.y, normal.z)) - V; 

            try{

                if (kt > 0) {
                    Transmitido = refracted (V, normal, Objectt->ior);
                    I = I + Render(cam, Recursao, ray(Colisao, Transmitido), Lights, recursao+1)*kt;
                }

                if(kr > 0){  
                    I = I + Render(cam, Recursao, ray(Colisao, Refletido), Lights, recursao+1)*kr;
                }

            }catch (int e){
                I = I + Render(cam, Recursao, ray(Colisao, Refletido), Lights, recursao+1);
            }
        }

    }


    return I;
}

/*Vector Render(const CAM &cam, const vector<Object*> &Objects, const ray &raio, const vector<Light> &Lights, int recursao) {
    vector<pair<double, Object*>> distances;
    double dist;
    Vector RGB;
    Object* Object;

    for(const auto& object : Objects) {
        dist = object->intersect(raio);
        if(dist != Not_intersect) {
            distances.push_back(make_pair(dist, object));
        }
    }

    if(distances.empty()) {
        return cam.cor / 255;
    }

    sort(distances.begin(), distances.end(), return_min_dist);
    dist = distances[0].first;
    Object = distances[0].second;

    if (dynamic_cast<Cylinder*>(Object)) {
        // Se o objeto é um cilindro, use a textura diretamente
        Cylinder* cyl = dynamic_cast<Cylinder*>(Object);
        RGB = cyl->getTextureColor(raio.at(dist));
    } else {
        // Caso contrário, use o modelo de iluminação Phong
        RGB = Phong(cam, Object, raio, dist, Lights, Objects, recursao);
    }
    
    return RGB;
}
*/

Vector Render(const CAM &cam, const vector<Object*> &Objects, const ray &raio, const vector<Light> &Lights, int recursao) {
    vector<pair<double, Object*>> distances;
    double dist;
    Vector RGB;
    Object* Object;

    for(const auto& object : Objects) {
        dist = object->intersect(raio);
        if(dist != Not_intersect) {
            distances.push_back(make_pair(dist, object));
        }
    }

    if(distances.empty()) {
        return cam.cor / 255;
    }

    sort(distances.begin(), distances.end(), return_min_dist);
    dist = distances[0].first;
    Object = distances[0].second;

    if (dynamic_cast<Cylinder*>(Object)) {
        // Se o objeto é um cilindro, use a textura diretamente
        Cylinder* cyl = dynamic_cast<Cylinder*>(Object);
        RGB = cyl->getTextureColor(raio.at(dist));
    } else if (dynamic_cast<Plane*>(Object)) {
        // Se o objeto é um plano, use a textura diretamente
        Plane* plane = dynamic_cast<Plane*>(Object);
        RGB = plane->getTextureColor(raio.at(dist));
    } else {
        // Caso contrário, use o modelo de iluminação Phong
        RGB = Phong(cam, Object, raio, dist, Lights, Objects, recursao);
    }
    
    return RGB;
}


int main(){

    double x, y, z, foo, height, length, distance;
    vector<Sphere> Spheres;
    vector<Plane> Planes;
    vector<Mesh> Meshs;
    vector<Light> Lights;
    vector<Cylinder> Cylinders;

    int nTriangles;
    int nVertex;
    vector<Point> Vertices;
    Vector color;
    Vector ambient_light;
    cin >> x >> y >> z;
    Point origin = Point(x, y, z);

    cin >> x >> y >> z;
    Point target = Point(x, y, z);

    cin >> x >> y >> z;
    Vector up = Vector(x, y, z);

    cin >> x >> y >> z;
    Vector cor = Vector(x, y, z);

    cin >> foo;
    height = foo;

    cin >> foo;
    length = foo;

    cin >> foo;
    distance = foo;

    cin >> x >> y >> z;
    ambient_light = Vector(x, y, z);

    CAM cam = CAM(origin, target, up, cor, height, length, distance, ambient_light);
    Vector sup_esquerdo = cam.W*(cam.distance) + cam.V - cam.U ;
    Vector passo_x = cam.U*(2/(length-1));
    Vector passo_y = cam.V*(2/(height-1));    

    for(string input = ""; input != "generate"; cin >> input){

        if (input == "light"){

            cin >> x >> y >> z;
            Point light_origin = Point (x, y, z);

            cin >> x >> y >> z;
            Vector light_intensity = Vector (x, y, z);

            Light light (light_origin, light_intensity);
            Lights.push_back(light);

        } else if(input == "sphere"){
        
            cin >> x >> y >> z;
            Point center = Point(x, y, z);
            
            cin >> x;
            double radius = x;

            cin >> x >> y >> z;
            Vector sp_color = Vector(x, y ,z);

            double kd, ks, ka, kr, kt, nrugo;
            cin >> kd >> ks >> ka >> kr >> kt >> nrugo;

            double ior = 1;
            
            Sphere sphere = Sphere(center, radius, sp_color, kd, ks, ka, kr, kt, nrugo, ior);
            Spheres.push_back(sphere);
        
        } else if(input == "plane"){

            cin >> x >> y >> z;
            Point plane_origin = Point(x, y, z);

            cin >> x >> y >> z;
            Vector plane_normal = Vector(x, y, z);

            cin >> x >> y >> z;
            Vector plane_cor = Vector(x, y, z);

            double kd, ks, ka, kr, kt, nrugo;
            cin >> kd >> ks >> ka >> kr >> kt >> nrugo;

            double ior = 1;
            
            std::string texture_file = "rosa60j.jpg";

            Plane plane = Plane(plane_origin, plane_normal, plane_cor, kd, ks, ka, kr, kt, nrugo, ior, texture_file);
            Planes.push_back(plane);
            
        }else if(input == "cylinder"){

            cin >> x >> y >> z;
            Point base = Point(x, y, z);

            cin >> x >> y >> z;
            Vector axis = Vector(x, y, z);

            cin >> foo;
            double radius = foo;

            cin >> foo;
            double height = foo;

            cin >> x >> y >> z;
            Vector cyl_color = Vector(x, y ,z);

            double kd, ks, ka, kr, kt, nrugo;
            cin >> kd >> ks >> ka >> kr >> kt >> nrugo;

            double ior = 1;

            Cylinder cylinder = Cylinder(base, axis, radius, height, cyl_color, kd, ks, ka, kr, kt, nrugo, ior, "rosa60j.jpg");

            //Cylinder cylinder = Cylinder(base, axis, radius, height, cyl_color, kd, ks, ka, kr, kt, nrugo, ior);
            Cylinders.push_back(cylinder);
        
        }else if(input == "mesh"){
            cin >> nTriangles;
            cin >> nVertex;
            vector<vector<int>> triplas (nTriangles);

            for(int i = 0; i < nVertex; i++){
                cin >> x >> y >> z;
                Point A = Point(x, y, z);
                Vertices.push_back(A);
            }
            for(int i=0; i<nTriangles; i++){
                cin >> x >> y >> z;
                triplas[i].push_back(x);
                triplas[i].push_back(y);
                triplas[i].push_back(z);
            }
            cin >> x >> y >> z;
            Vector mesh_color = Vector(x, y, z);

            double kd, ks, ka, kr, kt, nrugo;
            cin >> kd >> ks >> ka >> kr >> kt >> nrugo;

            double ior = 1.0;

            Mesh mesh = Mesh(nTriangles, nVertex, Vertices, triplas, mesh_color, kd, ks, ka, kr, kt, nrugo, ior);
            triplas.clear();
            Vertices.clear();

            Meshs.push_back(mesh);

        }else if(input == "transf"){
            string object, eixo;
            int index;
            bool rotate;
            double ang;

            //ex: sphere 2 (a terceira esfera)
            cin >> object >> index >> rotate;

            Matrix matrix = Matrix();
            if(rotate){
                cin >> eixo >> ang;
                matrix.elements = matrix.initialize(eixo, ang);

            }else{
                for(int i = 0; i < 4; i++){
                    for(int j = 0; j < 4; j++){
                        cin >> matrix.elements[i][j];
                    }
                }
            }

            if(object == "sphere"){
                Point center = matrix.transform_point(Spheres[index].center);
                Spheres[index] = Sphere(center, Spheres[index].radius, Spheres[index].color,
                                Spheres[index].kd, Spheres[index].ks, Spheres[index].ka, 
                                Spheres[index].kr, Spheres[index].kt, Spheres[index].nrugo, Spheres[index].ior);

            
            }else if(object == "plane"){
                Point origin = matrix.transform_point(Planes[index].point);
                Vector normal = matrix.transform_vector(Planes[index].normal);
                Planes[index] = Plane(origin, normal, Planes[index].color,
                          Planes[index].kd, Planes[index].ks, Planes[index].ka, 
                          Planes[index].kr, Planes[index].kt, Planes[index].nrugo, Planes[index].ior);

            }else if(object == "mesh"){
                vector<Point> newVertices;
                for (Point vertice : Meshs[index].Vertices) {
                    Point newVertice = matrix.transform_point(vertice);
                    newVertices.push_back(newVertice);
                }
                Meshs[index] = Mesh(Meshs[index].nTriangles, Meshs[index].nVertex, newVertices, Meshs[index].triplas, 
                                    Meshs[index].color, Meshs[index].kd, Meshs[index].ks, Meshs[index].ka, 
                                    Meshs[index].kr, Meshs[index].kt, Meshs[index].nrugo, Meshs[index].ior);
                newVertices.clear();
            }
        }
    }

    vector<Object*> Objects;
    for(Sphere& sphere : Spheres){Objects.push_back(&sphere);}
    for(Plane& plane : Planes){Objects.push_back(&plane);}
    for(Mesh& mesh : Meshs){Objects.push_back(&mesh);}
    for(Cylinder& cylinder : Cylinders){ Objects.push_back(&cylinder); }

    cout << "P3\n" << length << " " << height << "\n255\n";
    
    for(double y = 0; y < height; y++){
        for(double x = 0; x < length; x++){
            ray raio = ray(cam.origin, sup_esquerdo + (passo_x*x) - (passo_y*y));
            Vector RGB = Render(cam, Objects, raio, Lights, 0);
            RGB = RGB*255;
            RGB = Vector(min(255, int(RGB.x)), min(255, int(RGB.y)), min(255, int(RGB.z)));
            cout << RGB.x << " " << RGB.y << " " << RGB.z << endl;
        }
    }

    return 0;
}