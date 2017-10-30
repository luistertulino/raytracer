#ifndef DIRECTIONAL_H_
#define DIRECTIONAL_H_
#include "../Light.h"

class Directional : public Light{
  
  public:

    // Attributes
    Vector3 direction;

    // Constructors
    Directional() : Light(){
        direction = Vector3(1.0,1.0,1.0);
    }
    Directional(Vector3 &_direction, RGB &_intensity) : Light(_intensity){
        direction = _direction;
    }
  
    // Methods
    Vector3 get_direction(const Point3 &new_origin) const override;
};

Vector3 Direction::get_direction(const Point3 &new_origin) const {
    return direction;
}

#endif
