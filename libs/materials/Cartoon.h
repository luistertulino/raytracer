#ifndef CARTOON_H_
#define CARTOON_H_

#include "../Material.h"

class Cartoon : public Material{
public:
  RGB shadow;
  RGB outline;

  // Cartoon(RGB albedo, RGB sdw, RGB otln):Material(albedo){shadow = sdw; outline = otln;};

  Cartoon(Texture *t, RGB &sdw, RGB &otln):Material(t){shadow = sdw; outline = otln;};

  bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const override;
};

bool Cartoon::scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const {

  return true;
}
#endif
