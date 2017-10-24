#ifndef LIGHT_H_
#define LIGHT_H_
#include "utility/Ray.h"
#include "Scene.h"

class Light{

  public:

	// Attributes
	RGB intensity;

    // Constructors
    Light(){
		intensity = RGB(1.0,1.0,1.0);
    }
	Light(RGB _intensity){
		intensity = _intensity;
	}

    // Methods
    virtual Vector3 get_direction(const Point3 &new_origin) const = 0;

};

#endif
