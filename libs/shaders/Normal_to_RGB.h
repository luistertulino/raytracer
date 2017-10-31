#ifndef NORMAL_TO_RGB_H_
#define NORMAL_TO_RGB_H_
#include "../Shader.h"

  class Normal_to_RGB : public Shader{
  public:
    //Constructors

    Normal_to_RGB():Shader(){};

    RGB shade(const Ray &ray, Scene &scene) const override;

  };

  RGB Normal_to_RGB::shade(const Ray &ray, Scene &scene) const {

    double max_t = std::numeric_limits<double>::max(); //most distant object
    double min_t = 0.0; //camera distance

    Vector3 rgb_to_paint;
    hit_record rec;

    //if hit an object
    if(scene.hit_anything(ray, min_t, max_t, rec)){

      rgb_to_paint = 0.5 * (rec.normal + Vector3(1,1,1)); //color to paint is a "normalized" normal

    }
    else{

      rgb_to_paint = interpolate_background(ray, scene.get_background());

    }

    return rgb_to_paint;
  }
#endif
