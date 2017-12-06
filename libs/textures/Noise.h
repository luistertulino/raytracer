#ifndef NOISE_H_
#define NOISE_H_

#include "../Texture.h"
#include "../utility/Perlin.h"

class Noise : public Texture{
public:
  RGB color;
  Perlin noise;
  double scale;

  Noise(RGB &color, double scale = 1) : color(color), scale(scale){
    noise = Perlin();
  }

  virtual RGB value(double u, double v, const Point3& p) const override;
};

RGB Noise::value(double u, double v, const Point3& p) const {
  return color * 0.5 * ( 1 + sin(scale * p.x() 
                        + 5 * noise.turb(scale * p)) );
}

#endif
