#ifndef IMAGE_TEXTURE_H_
#define IMAGE_TEXTURE_H_

#define STB_IMAGE_IMPLEMENTATION
#include "../utility/stb_image.h"

#include "../Texture.h"

class Image_Texture : public Texture {
public:
    unsigned char *data;
    int nx, ny;

    Image_Texture(){}
    Image_Texture(std::string &path){
        const char *filename;
        filename = path.c_str();

        int nn;
        data = stbi_load(filename, &nx, &ny, &nn, 0);
    }
    //Image(unsigned char *pixels, int A, int B) : data(pixels), nx(A), ny(B) {}
    
    virtual RGB value(double u, double v, const Point3 &p) const override;
        
};

RGB Image_Texture::value(double u, double v, const Point3 &p) const {
    int i = (  u)*nx;
    int j = (1-v)*ny-0.001;

    if (i < 0) i = 0;
    if (j < 0) j = 0;
    if (i > nx-1) i = nx-1;
    if (j > ny-1) j = ny-1;

    double r = int(data[3*i + 3*nx*j]  ) / 255.0;
    double g = int(data[3*i + 3*nx*j+1]) / 255.0;
    double b = int(data[3*i + 3*nx*j+2]) / 255.0;

    return RGB(r, g, b);
}

#endif
