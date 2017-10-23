#ifndef METAL_H_
#define METAL_H_

#include "../Material.h"
#include <cmath>


class Metal : public Material{
  double fuzziness;
public:
  //Constructors
  Metal(double fuzz = 0):Material(){fuzziness = std::min(1.0,fuzz);}
  Metal(RGB rgb_, double fuzz = 0 ):Material(rgb_){fuzziness = std::min(1.0,fuzz);}
  
  //Methods
  bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const override;
};

bool Metal::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {
  Vector3 reflected = reflect(unit_vector(ray_in.get_direction()), rec.normal);
  Point3 origin = rec.p + 0.01 * rec.normal;
  Vector3 target = unit_vector(reflected + fuzziness*random_vector_in_unit_sphere());
  scattered = Ray(origin, target);
  if(dot(scattered.get_direction(),rec.normal) > 0){
    return true;
  }
  else{
    return false;
  }
}

#endif
