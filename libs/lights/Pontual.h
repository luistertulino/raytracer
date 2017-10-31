#ifndef PONTUAL_H_
#define PONTUAL_H_
#include "../Light.h"

class Pontual : public Light{
  
  public:

    // Attributes
    Point3 source;

    // Constructors
    Pontual(Point3 _source = Point3(0.0,0.0,0.0)) : Light(){
        source = _source;
    }
    Pontual(Point3 _source, RGB _intensity) : Light(_intensity){
        source = _source;
    }
  
    // Methods
    Vector3 get_direction(const Point3 &new_origin) const override;
    //bool is_shadow(const Point3 &new_origin, const Scene &scene, Vector3 &light_direction);
};

Vector3 Pontual::get_direction(const Point3 &new_origin) const {
    return source - new_origin;
}

/*bool Pontual::is_shadow(const Point3 &new_origin, const Scene &scene, Vector3 &light_direction){

    light_direction = unit_vector(get_direction(new_origin));
    Ray new_ray(new_origin, light_direction);

    hit_record rec;
    if(scene.hit_first_object(new_ray, rec)){
        return true;
    }
    return false;
}*/

#endif
