#include "../Texture.h"

class Solid : public Texture{
  public:
    Vector3 color;

    Solid();
    Solid(Vector3 &c){
        color = c;
    }

    virtual Vector3 value(float u, float v, const Vector3 &p) const override;
    
};

Vector3 Solid::value(float u, float v, const Vector3 &p) const {
    return color;
}