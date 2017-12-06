#ifndef NORMAL_MATERIAL_H_
#define NORMAL_MATERIAL_H_

#include "../Material.h"

class Normal_Material : public Material{
public:
  Normal_Material():Material(){};
  
  bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const override;
};

bool Normal_Material::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {
  scattered = rec.normal;
  return true;
}

#endif
