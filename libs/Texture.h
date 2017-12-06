#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "utility/Vector3.h"

class Texture{
  public:
    Texture(){}

    virtual RGB value(double u, double v, const Vector3 &p) const = 0;
    
};

#endif