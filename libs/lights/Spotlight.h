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
    Vector3 direction;
    double angle, angle_cos;
    double attenuation;
    double temp_cos; // This variable is used to store temporarily the cossin between the direction and the vector between the point and the source

    // Constructors
    Spotlight() : Light(){
        source = Point3(0.0,0.0,0.0);
        direction = unit_vector( Vector3(1.0,1.0,1.0) );
        angle = 45.0;
        angle_cos = std::cos(angle * M_PI/180);
        attenuation = 0.5;
    }
    Spotlight(Point3 &_source, Vector3 &_direction, double _angle, double _attenuation, RGB &_intensity, ) : Light(_intensity){
        source = _source;
        direction = unit_vector(_direction);
        angle = _angle;
        angle_cos = std::cos(angle * M_PI/180);
        attenuation = _attenuation;
    }
  
    // Methods
    virtual Vector3 get_direction(const Point3 &new_origin) const override;
    bool is_shadow(const Point3 &new_origin, const Scene &scene, Vector3 &light_direction) const override;
    RGB get_intensity() const override;
}

Vector3 Spotlight::get_direction(const Point3 &new_origin) const {
    return source - new_origin;
}

bool Spotlight::is_shadow(const Point3 &new_origin, const Scene &scene, Vector3 &light_direction){
    light_direction = unit_vector(get_direction(new_origin));
    Ray new_ray(new_origin, light_direction);

    hit_record rec;
    if(scene.hit_first_object(ray, rec)){
        return true;
    }

    temp_cos = dot(direction, light_direction);
    
    if(temp_cos < angle_cos) return true;
    return false;
}

RGB get_intensity(){
    if (temp_cos >= angle_cos) return intensity * attenuation * temp_cos;
    return RGB(0.0,0.0,0.0);
}











