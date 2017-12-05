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

    virtual Vector3 value(float u, float v, const Vector3 &p) const override;
    
};

Vector3 Checker::value(float u, float v, const Vector3 &p) const {
    float sines = sin(10 * p.X()) * sin(10 * p.Y()) * sin(10 * p.Z()); 

    if (sines < 0)
    {
        return odd->value(u, v, p);
    }
    else{
        return even->value(u, v, p);
    }
}