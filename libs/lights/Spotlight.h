#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_
#include "../Light.h"

class Spotlight : public Light{
  
  public:

    // Attributes
    Point3 source;
    Vector3 direction;
    double angle;
    double attenuation;

    // Constructors
    Spotlight() : Light(){
        source = Point3(0.0,0.0,0.0);
        direction = unit_vector( Vector3(1.0,1.0,1.0) );
        angle = 45.0;
        attenuation = 0.5;
    }
    Spotlight(Point3 &_source, Vector3 &_direction, double _angle, double _attenuation, RGB &_intensity, ) : Light(_intensity){
        source = _source;
        direction = _direction;
        angle = _angle;
        attenuation = _attenuation;
    }
  
    // Methods
    virtual Vector3 get_direction(const Point3 &new_origin) const override;
    bool is_shadow(const Point3 &new_origin, const Scene &scene, Vector3 &light_direction) const override;
}

Vector3 Pontual::get_direction(const Point3 &new_origin) const {
    return direction;
}

bool Spotlight::is_shadow(const Point3 &new_origin, const Scene &scene, Vector3 &light_direction){
}
