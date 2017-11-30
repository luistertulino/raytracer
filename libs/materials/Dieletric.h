#ifndef DIELETRIC_H_
#define DIELETRIC_H_

#include <cmath>
#include <random>
#include "../Material.h"

class Dieletric : public Material{
public:
  //Constructors
  double ref_idx;

  Dieletric():Material(){ ref_idx = 1.0; }

  Dieletric(RGB &color):Material(color){
    ref_idx = 1.0;
  }

  Dieletric(RGB &color, double ref_idx_):Material(color){
    ref_idx = ref_idx_;
  }

  bool   refract(const Vector3 &v, const Vector3 &n, double ni_over_nt, Vector3 &refracted) const;
  double schlick(float cosine, float ref_idx) const;
  bool   scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const override;
};

bool Dieletric::refract(const Vector3 &v, const Vector3 &n, double ni_over_nt, Vector3 &refracted) const{
  double dt = dot(unit_vector(v), n);
  double discriminant = 1.0 - ni_over_nt*ni_over_nt * (1 - dt*dt);

  if (discriminant > 0.0){
    refracted = ni_over_nt * (v - n * dt) - n * sqrt(discriminant);
    return true;
  }
  return false;
}

double Dieletric::schlick(float cosine, float ref_idx) const {
  double r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 = r0*r0;

  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Dieletric::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {
  Vector3 outward_normal;
  Vector3 refracted; 
  Vector3 reflected = reflect(ray_in.get_direction(), rec.normal); 
  double ni_over_nt, reflect_prob, cosine;
  
  double dot_ray_normal = dot(ray_in.get_direction(), rec.normal);
  if( dot_ray_normal > 0.0 )
  {
    outward_normal = -rec.normal;
    ni_over_nt = ref_idx;
    cosine = ref_idx * dot_ray_normal / ray_in.get_direction().length();
  }
  else{
    outward_normal = rec.normal;
    ni_over_nt = 1.0 / ref_idx;
    cosine = -dot_ray_normal / ray_in.get_direction().length();
  }

  if (refract(ray_in.get_direction(), outward_normal, ni_over_nt, refracted))
  {
    reflect_prob = schlick(cosine, ref_idx);
  }
  else{
    scattered = Ray(rec.p, reflected);
    reflect_prob = 1;
  }

  if(std::generate_canonical<double, std::numeric_limits<double>::digits>(random_generator) > reflect_prob){
    scattered = Ray(rec.p, refracted);
  }
  else{
    scattered = Ray(rec.p, reflected);
  }

  return true;
}

#endif
