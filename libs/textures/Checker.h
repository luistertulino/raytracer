#ifndef CHECKER_H_
#define CHECKER_H_

#include "../Texture.h"

#include <cmath>

class Checker : public Texture{
  public:
    Texture *odd, *even;

    Checker();
    Checker(Texture *t0, Texture *t1){
        even = t0;
        odd  = t1;
    }

    virtual RGB value(double u, double v, const Point3 &p) const override;
    
};

RGB Checker::value(double u, double v, const Point3 &p) const {
    float sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z()); 

    if (sines < 0)
    {
        return odd->value(u, v, p);
    }
    else{
        return even->value(u, v, p);
    }
}

#endif