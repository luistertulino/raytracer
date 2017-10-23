#ifndef SHINY_H_
#define SHINY_H_

#include "../Material.h"

class Shiny : public Material{
public:
  RGB k_a, k_d, k_s;
  double specular_exponent;
  //Constructors
  Shiny(double exponent = 4):Material(RGB(0)){
    k_a = k_d = k_s = RGB(0);
    albedo = k_d;
    specular_exponent = exponent;
  }
  Shiny(RGB k_a_, RGB k_d_, RGB k_s_, double exponent = 4):Material(k_d_){
    k_a = k_a_;
    k_d = k_d_;
    k_s = k_s_;
    albedo = k_d;
    specular_exponent = exponent;
  }
  bool scatter(const Ray &ray_in,  const hit_record &rec, Ray &scattered) const override;
};
bool Shiny::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {
  return true;
}
#endif
