#ifndef SOLID_H_
#define SOLID_H_

#include "../Texture.h"

class Solid : public Texture{
  public:
    RGB color;

    Solid(){
    	color = RGB(0.0);
    }
    Solid(RGB &c){
        color = c;
    }

    virtual RGB value(double u, double v, const Point3 &p) const override;
    
};

RGB Solid::value(double u, double v, const Point3 &p) const {
    return color;
}

#endif