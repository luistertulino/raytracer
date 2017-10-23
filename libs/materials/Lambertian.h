#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "../Material.h"

class Lambertian : public Material{
public:
  //Constructors
  RGB k_a;

  Lambertian():Material(){}
  Lambertian(RGB rgb):Material(rgb){k_a = RGB(0);}
  Lambertian(RGB k_a_, RGB albedo):Material(albedo){k_a = k_a_;}
  bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const override;
};

bool Lambertian::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {
  Vector3 target = rec.p + rec.normal + random_vector_in_unit_sphere();
  Point3 origin = rec.p + 0.01 * rec.normal;
  scattered = Ray(origin, target - origin);
  return true;
}

#endif
