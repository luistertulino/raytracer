#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_
#include "../Light.h"
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class Spotlight : public Light{
  
  public:

    // Attributes
    Point3 source;
    Point3 destination;
    Vector3 direction;
    double angle, angle_cos;
    double attenuation;
    double cos_ray_direction; // This variable is used to store temporarily the cossin between the direction and the vector between the point and the source

    // Constructors
    Spotlight() : Light(){
        source = destination = Point3(0.0,0.0,0.0);
        direction = destination;// - source;
        angle = 45.0;
        angle_cos = std::cos(angle * M_PI/180);
        attenuation = 0.5;
    }
    Spotlight(Point3 &_source, Point3 &_destination, double _angle, double _attenuation, RGB &_intensity) : Light(_intensity){
        source = _source;
        destination = _destination;
        direction = unit_vector(destination - source);
        angle = _angle;
        angle_cos = std::cos(angle * M_PI/180);
        attenuation = _attenuation;
    }
  
    // Methods
    Vector3 get_direction(const Point3 &new_origin) const override;
    
    RGB get_intensity();
};

Vector3 Spotlight::get_direction(const Point3 &new_origin) const {
    return source - new_origin;
}

RGB Spotlight::get_intensity(){
    if (cos_ray_direction > angle_cos) return intensity * attenuation * cos_ray_direction;
    return RGB(0.0,0.0,0.0);
}

#endif
