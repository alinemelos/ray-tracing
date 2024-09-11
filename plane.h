/*#ifndef PLANEH
#define PLANEH

#include "vector.h"
#include "point.h"
#include "objects.h"
#include "ray.h"
using namespace std;
#define Not_intersect -1
#define Discard 1e-6


class Plane: public Object {
public:
    double a, b, c, d; // Coeficientes do plano
    Point point;
    Vector normal;

    Plane(const Point& point, const Vector& normal, const Vector& color, double kd, double ks, double ka, double kr, double kt, double nrugo, double ior) 
    : point(point), normal(normal), Object(color, kd, ks, ka, kr, kt, nrugo, ior) {
        a = normal.x;
        b = normal.y;
        c = normal.z;
        //a*x + b*y + c*z + d = 0 -> d = -(a*x + b*y + c*z)
        d = -(a * point.x + b * point.y + c * point.z);
    }

    double intersect(const ray &r) override {
        auto condition = normal.dot(r.direction().x, r.direction().y, r.direction().z);
        if(abs(condition) < Discard){return Not_intersect;}
        
        double distance = (normal.dot(point.x, point.y, point.z) - normal.dot(r.origin().x, r.origin().y, r.origin().z)) / normal.dot(r.direction().x, r.direction().y, r.direction().z);
        if(distance > Discard){
            return distance;
        }
        return Not_intersect;
    }

    // retorna a normal que definida na inicialização
    // é constante ao longo de todo o plano
    Vector returnNormal(const ray& r, double t) override {

         // inverte a direção da normal se ela for igual a direção do raio
        if(r.direction().dot(normal.x, normal.y, normal.z) > 0){normal = normal*(-1);}

        return normal;
    }

    Vector normalVector() const {
        return Vector(a, b, c);
    }

    bool contains(const Point& point) const {
        return (a * point.x + b * point.y + c * point.z + d) == 0;
    }
};

#endif
*/

#ifndef PLANEH
#define PLANEH

#include "vector.h"
#include "point.h"
#include "objects.h"
#include "ray.h"
#include "stb_image.h" // stb_image para carregamento de texturas
using namespace std;
#define Not_intersect -1
#define Discard 1e-6

class Plane: public Object {
public:
    double a, b, c, d; // Coeficientes do plano
    Point point;
    Vector normal;
    unsigned char* texture_data; // Armazenamento da textura
    int texture_width, texture_height, texture_channels;

    Plane(const Point& point, const Vector& normal, const Vector& color, double kd, double ks, double ka, double kr, double kt, double nrugo, double ior, const std::string& texture_file = "") 
    : point(point), normal(normal), Object(color, kd, ks, ka, kr, kt, nrugo, ior) {
        a = normal.x;
        b = normal.y;
        c = normal.z;
        //a*x + b*y + c*z + d = 0 -> d = -(a*x + b*y + c*z)
        d = -(a * point.x + b * point.y + c * point.z);

        if (!texture_file.empty()) {
            texture_data = stbi_load(texture_file.c_str(), &texture_width, &texture_height, &texture_channels, 0);
            if (!texture_data) {
                std::cerr << "Failed to load texture: " << texture_file << std::endl;
            }
        } else {
            texture_data = nullptr;
        }
    }

    ~Plane() {
        if (texture_data) {
            stbi_image_free(texture_data);
        }
    }

    double intersect(const ray &r) override {
        auto condition = normal.dot(r.direction().x, r.direction().y, r.direction().z);
        if(abs(condition) < Discard){return Not_intersect;}
        
        double distance = (normal.dot(point.x, point.y, point.z) - normal.dot(r.origin().x, r.origin().y, r.origin().z)) / normal.dot(r.direction().x, r.direction().y, r.direction().z);
        if(distance > Discard){
            return distance;
        }
        return Not_intersect;
    }

    Vector getTextureColor(const Point& p) const {
        if (!texture_data) {
            return color;
        }

        // Mapear a posição da colisão no plano para coordenadas de textura
        double u = fmod(abs(p.x), 1.0);
        double v = fmod(abs(p.z), 1.0);

        int i = u * texture_width;
        int j = v * texture_height;

        int index = (j * texture_width + i) * texture_channels;

        double r = texture_data[index] / 255.0;
        double g = texture_data[index + 1] / 255.0;
        double b = texture_data[index + 2] / 255.0;

        return Vector(r, g, b);
    }

    // Retorna a normal que é constante ao longo de todo o plano
    Vector returnNormal(const ray& r, double t) override {
         // Inverte a direção da normal se ela for igual a direção do raio
        if(r.direction().dot(normal.x, normal.y, normal.z) > 0){normal = normal*(-1);}
        return normal;
    }

    Vector normalVector() const {
        return Vector(a, b, c);
    }

    bool contains(const Point& point) const {
        return (a * point.x + b * point.y + c * point.z + d) == 0;
    }
};

#endif

