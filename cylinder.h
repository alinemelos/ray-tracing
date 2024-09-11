/*#ifndef CYLINDER_H
#define CYLINDER_H

#include "objects.h"
#include "ray.h"
#include "vector.h"
#include "point.h"
#include "image.h" // Certifique-se de incluir a sua classe Image

class Cylinder : public Object {
public:
    Point base;  // Ponto da base do cilindro
    Vector axis; // Vetor de direção do eixo do cilindro
    double radius;
    double height;
    Image texture; // Membro para armazenar a textura

    Cylinder(Point base, Vector axis, double radius, double height, Vector color,
             double kd, double ks, double ka, double kr, double kt, double nrugo, double ior,
             const Image& texture)
        : Object(color, kd, ks, ka, kr, kt, nrugo, ior),
          base(base), axis(axis), radius(radius), height(height), texture(texture) {
        axis.make_unit_vector(); // Normalizar o eixo
    }

    double intersect(const ray &r) override {
        Vector d = r.direction() - (axis * (r.direction().dot(axis.x, axis.y, axis.z)));
        Vector delta_p = r.origin() - base;
        Vector dp = delta_p - (axis * (delta_p.dot(axis.x, axis.y, axis.z)));

        double a = d.dot(d.x, d.y, d.z);
        double b = 2 * dp.dot(d.x, d.y, d.z);
        double c = dp.dot(dp.x, dp.y, dp.z) - radius * radius;

        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) return Not_intersect;

        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);

        double z1 = (r.at(t1) - base).dot(axis.x, axis.y, axis.z);
        double z2 = (r.at(t2) - base).dot(axis.x, axis.y, axis.z);

        // No método intersect
        /*if (t1 > Discard && z1 >= 0 && z1 <= height) {
            this->color = Vector(255, 0, 0); // Cor sólida (vermelho)
            return t1;
        }

        if (t2 > Discard && z2 >= 0 && z2 <= height) {
            this->color = Vector(255, 0, 0); // Cor sólida (vermelho)
            return t2;
        }


        return Not_intersect;
    }


    Vector returnNormal(const ray& r, double t) override {
        Point P = r.at(t);
        Vector n = (P - base) - axis * ((P - base).dot(axis.x, axis.y, axis.z));
        n.make_unit_vector();
        return n;
    }

    // Método para obter a cor da textura no ponto P
    Vector getTextureColor(const Point& P) {
        // Coordenada u: ângulo ao redor do eixo do cilindro
        double theta = atan2(P.z - base.z, P.x - base.x);
        if (theta < 0) theta += 2 * M_PI; // Normaliza o ângulo entre 0 e 2*PI
        double u = theta / (2 * M_PI); // Normaliza o valor de u entre 0 e 1

        // Coordenada v: posição ao longo da altura do cilindro
        double v = (P.y - base.y) / height; // Normaliza o valor de v entre 0 e 1

        // Pega a cor da textura com base em u e v
        return texture.getColor(u, v);
    }
    Vector getTextureColor(const Point& P) {
        double theta = atan2(P.z - base.z, P.x - base.x);
        if (theta < 0) theta += 2 * M_PI;
        double u = theta / (2 * M_PI);

        double v = (P.y - base.y) / height;

        std::cout << "u: " << u << ", v: " << v << std::endl; // Depuração

        return texture.getColor(u, v);
    }

};

#endif*/

#ifndef CYLINDER_H
#define CYLINDER_H
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "objects.h"
#include "ray.h"
#include "vector.h"
#include "point.h"

class Cylinder : public Object {
public:
    Point base;  // Ponto da base do cilindro
    Vector axis; // Vetor de direção do eixo do cilindro
    double radius;
    double height;

    unsigned char* textureData;
    int textureWidth, textureHeight, textureChannels;

    /*Cylinder(Point base, Vector axis, double radius, double height, Vector color,
             double kd, double ks, double ka, double kr, double kt, double nrugo, double ior)
        : Object(color, kd, ks, ka, kr, kt, nrugo, ior),
          base(base), axis(axis), radius(radius), height(height) {
        axis.make_unit_vector(); // Normalizar o eixo
    }*/

    Cylinder(Point base, Vector axis, double radius, double height, Vector color,
             double kd, double ks, double ka, double kr, double kt, double nrugo, double ior,
             const char* texturePath)
        : Object(color, kd, ks, ka, kr, kt, nrugo, ior), base(base), axis(axis), radius(radius), height(height) {
        axis.make_unit_vector(); // Normalizar o eixo
        textureData = stbi_load(texturePath, &textureWidth, &textureHeight, &textureChannels, 0);
        if (textureData == nullptr) {
            std::cerr << "Failed to load texture" << std::endl;
        }
    }

    ~Cylinder() {
        if (textureData) {
            stbi_image_free(textureData);
        }
    }

    double intersect(const ray &r) override {
        // Implementação da interseção de um raio com um cilindro
        Vector d = r.direction() - (axis * (r.direction().dot(axis.x, axis.y, axis.z)));
        Vector delta_p = r.origin() - base;
        Vector dp = delta_p - (axis * (delta_p.dot(axis.x, axis.y, axis.z)));

        double a = d.dot(d.x, d.y, d.z);
        double b = 2 * dp.dot(d.x, d.y, d.z);
        double c = dp.dot(dp.x, dp.y, dp.z) - radius * radius;

        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) return Not_intersect;

        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);

        // Verificar se as interseções estão dentro dos limites do cilindro
        double z1 = (r.at(t1) - base).dot(axis.x, axis.y, axis.z);
        double z2 = (r.at(t2) - base).dot(axis.x, axis.y, axis.z);

        if (t1 > Discard && z1 >= 0 && z1 <= height) return t1;
        if (t2 > Discard && z2 >= 0 && z2 <= height) return t2;

        return Not_intersect;
    }

    Vector returnNormal(const ray& r, double t) override {
        Point P = r.at(t);
        Vector n = (P - base) - axis * ((P - base).dot(axis.x, axis.y, axis.z));
        n.make_unit_vector();
        return n;
    }

    Vector getTextureColor(const Point& P) {
        Vector toP = P - base;
        double z = (toP.x * axis.x + toP.y * axis.y + toP.z * axis.z) / height;
        double theta = atan2(toP.y, toP.x); // Ângulo
        double u = (theta + M_PI) / (2 * M_PI); // Coordenada U 
        double v = (z + height / 2) / height; // Coordenada V 

        int x = int(u * textureWidth) % textureWidth;
        int y = int(v * textureHeight) % textureHeight;
        int index = (y * textureWidth + x) * textureChannels;

        Vector texColor;
        if (textureChannels >= 3) {
            texColor.x = textureData[index] / 255.0;
            texColor.y = textureData[index + 1] / 255.0;
            texColor.z = textureData[index + 2] / 255.0;
        } else {
            texColor = Vector(255, 255, 255); // Branco caso não tenha canais de cor suficientes
        }

        return texColor;
    }

};

#endif
