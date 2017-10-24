#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_
#include "../Light.h"

class Spotlight : public Light{
  
  public:

    // Attributes
    Point3 source;

    // Constructors
    Spotlight(Point3 _source = Point3(0.0,0.0,0.0)) : Light(){
        source = _source;
    }
    Spotlight(Point3 _source, RGB _intensity) : Light(_intensity){
        source = _source;
    }
  
    // Methods
    virtual Vector3 get_direction(const Point3 &new_origin) const override;
}

Vector3 Pontual::get_direction(const Point3 &new_origin) const {
    return source - new_origin;
}
