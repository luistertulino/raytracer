#ifndef CEL_H_
#define CEL_H_
#include "../Shader.h"
#include <vector>
#include <cmath>
#include <algorithm>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class Cel : public Shader{
public:
  std::vector<int> shading_intervals;
  int outline_threshold;

  Cel(int threshold = 80):Shader(){
    shading_intervals.push_back(threshold);
    outline_threshold = threshold;
  }

  Cel(std::vector<int> &intervals, double threshold = 80):Shader(){
    if(intervals.empty()){
      intervals.push_back(85);
    }
    std::sort(intervals.begin(), intervals.end());
    shading_intervals = intervals;
    outline_threshold = threshold;
   }

  virtual RGB shade(const Ray &ray, Scene &scene) const override; //Override method from Shader.h

};

RGB Cel::shade(const Ray &ray, Scene &scene) const{
  double max_t = std::numeric_limits<double>::max();
  double min_t = 0.0;

  RGB rgb_to_paint = RGB(0);
  hit_record rec;


  if(scene.hit_anything(ray, min_t, max_t, rec)){
    Cartoon *cartoon = dynamic_cast<Cartoon*>(rec.material);
    if(cartoon == nullptr){
      std::cerr << "not cartoon material" << '\n';
      return RGB(0);
    }

    double cos_cam_normal = dot(-ray.get_direction(), rec.normal);
    double cos_outline = std::cos(outline_threshold * M_PI/180);

    if(cos_cam_normal > cos_outline){

      auto lights = scene.get_lights();
      Point3 new_origin = rec.p + rec.normal * 0.01;

      double max_cos = -1;

      for(auto light : lights){
        Vector3 light_direction;

        if(scene.is_shadow(new_origin, light, light_direction)){
          rgb_to_paint += cartoon->shadow;

          continue;
        }

        double cos_light_normal = dot(light_direction, rec.normal);

        for(double interval : shading_intervals){

          double cos_interval = std::cos(interval * M_PI/180);
          //double u, v; u = v = 0.0; // This will change

          if(cos_light_normal >= cos_interval){

            if(cos_interval > max_cos){
              max_cos = cos_interval;
              rgb_to_paint = cartoon->color(rec.u, rec.v, rec.p) * max_cos * light->get_intensity();
              break;
            }

          }
          else if(interval == shading_intervals[shading_intervals.size()-1]){
            
            if(cos_interval > max_cos){
              max_cos = cos_interval;
              rgb_to_paint = cartoon->color(rec.u, rec.v, rec.p) * max_cos * light->get_intensity();
            }

          }
        }
        // rgb_to_paint = RGB(0,1,0) * max_cos * light.intensity;
      }
      rgb_to_paint[0] = std::min(1.0, rgb_to_paint[0]);
      rgb_to_paint[1] = std::min(1.0, rgb_to_paint[1]);
      rgb_to_paint[2] = std::min(1.0, rgb_to_paint[2]);
    }
    else{
      rgb_to_paint = cartoon->outline;
    }
  }
  else{
    rgb_to_paint = interpolate_background(ray, scene.get_background());
  }
  return rgb_to_paint;
};

#endif
