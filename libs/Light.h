#ifndef LIGHT_H_
#define LIGHT_H_
#include "utility/Ray.h"
#include "Scene.h"

class Light{

  public:

    // Attributes
    RGB intensity;

    // Constructors
    Light(RGB _intensity = RGB(1.0,1.0,1.0)){
        intensity = _intensity;
    }

    // Methods
    virtual Vector3 get_direction(const Point3 &new_origin) const = 0;
    
    RGB get_intensity(){
        return intensity;
    }

    bool is_shadow(const Point3 &new_origin, const Scene &scene, Vector3 &light_direction){

        light_direction = unit_vector(get_direction(new_origin));
        Ray new_ray(new_origin, light_direction);

        hit_record rec;
        if(scene.hit_first_object(new_ray, rec)){
            return true;
        }
        return false;
    }

};

#endif
