#ifndef DEPTH_MAP_H_
#define DEPTH_MAP_H_
#include "../Shader.h"

  class Depth_map : public Shader{
  public:
    double max_depth;

    //Constructors
    Depth_map():Shader(){
      max_depth = 4.0;
    }

    Depth_map(double depth):Shader(){
      max_depth = depth;
    }

    //Methods
    virtual RGB shade(const Ray &ray, Scene &scene) const override; //Override method from Shader.h

  };

  RGB Depth_map::shade(const Ray &ray, Scene &scene) const{

    double max_t = std::numeric_limits<double>::max();
    double min_t = 0.0;

    Vector3 rgb_to_paint;
    hit_record rec;

    RGB background_color(1,1,1); //White background
	  RGB foreground_color(0,0,0); //Black foreground

    if(scene.hit_anything(ray, min_t, max_t, rec)){


  	  double depth = (rec.p - ray.get_origin()).length(); //Distance from ray origin to hit point
  	  depth /= max_depth; //Normalize to [0,1]

  	  // evading color overflow
  	  if(depth > 1){
  	    depth = 1.0;
  	  }

      //Interpolate the depth found with the background
  	  rgb_to_paint = (1.0 - depth) * (foreground_color) + depth * background_color;

      return rgb_to_paint;
    }

    //If didn't hit, return white
    return background_color;

  }
#endif
