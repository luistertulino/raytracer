#ifndef STANDARD_SHADER_H_
#define STANDARD_SHADER_H_
#include "../Shader.h"

class Standard_shader : public Shader{
  public:
    //Constructors

    Standard_shader():Shader(){};

    RGB shade(const Ray &ray, Scene &scene) const override;

};

RGB Standard_shader::shade(const Ray &ray, Scene &scene) const {

  double max_t = std::numeric_limits<double>::max(); //most distant object
  double min_t = 0.0; //camera distance

  Vector3 rgb_to_paint;
  hit_record rec;

  //if hit an object
  if(scene.hit_anything(ray, min_t, max_t, rec)){

    //double u, v; u = v = 0.0; //This will change
    rgb_to_paint = rec.material->color(rec.u, rec.v, rec.p);
  }
  else{
    rgb_to_paint = interpolate_background(ray, scene.get_background());
  }

  return rgb_to_paint;
}
#endif
