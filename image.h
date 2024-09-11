#ifndef IMAGE_H
#define IMAGE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "vector.h"

class Image {
public:
    Image() : width(0), height(0), channels(0), data(nullptr) {}

    ~Image() {
        if (data) {
            stbi_image_free(data);
        }
    }

    bool load(const char* filename) {
        // Carregar a imagem usando stb_image
        data = stbi_load(filename, &width, &height, &channels, 0);
        if (!data) {
            std::cerr << "Erro ao carregar a imagem: " << stbi_failure_reason() << std::endl;
            return false;
        }
        return true;
    }

    Vector getColor(double u, double v) const {
        if (!data) {
            std::cerr << "Imagem não carregada." << std::endl;
            return Vector(0, 0, 0); // Retorna preto se a imagem não foi carregada
        }

        // Normalizar u e v para valores inteiros de pixel
        int x = static_cast<int>(u * (width - 1));
        int y = static_cast<int>(v * (height - 1));

        // Garantir que x e y estão dentro dos limites da imagem
        x = std::max(0, std::min(x, width - 1));
        y = std::max(0, std::min(y, height - 1));

        // Acessar a cor no pixel (x, y)
        int index = (y * width + x) * channels;
        double r = data[index] / 255.0;
        double g = (channels > 1) ? data[index + 1] / 255.0 : r;
        double b = (channels > 2) ? data[index + 2] / 255.0 : r;

        return Vector(r, g, b); // Retornar a cor como um vetor
    }

private:
    int width, height, channels;
    unsigned char* data;
};

#endif
