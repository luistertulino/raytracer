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

    bool is_shadow(const Point3 &new_origin, const Scene &scene, Vector3 &light_direction);

};

#endif
