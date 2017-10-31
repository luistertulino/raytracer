#ifndef RECURSIVE_H_
#define RECURSIVE_H_

#include "../Shader.h"
#include <random>
#include <algorithm>

class Recursive : public Shader{

  int iterations; //Number of iterations

public:

  //===>Constructors
  Recursive(int iter = 1):Shader(){ iterations = iter;}

  //Calls the other shade with iterations
  RGB shade(const Ray &ray, Scene &scene) const override;

  //Actually gets the color
  RGB shade(const Ray &ray, Scene &scene, int actual_iteration) const;

};

  //real color function, with number of iterations
  RGB Recursive::shade(const Ray &ray, Scene &scene, int actual_iteration) const {
    double max_t = std::numeric_limits<double>::max();
    double min_t = 0.0;

    Vector3 rgb_to_paint;
    hit_record rec;

    if(scene.hit_anything(ray, min_t, max_t, rec)){

      if(actual_iteration > 0){ //para chamadas recursivas
        // creates new ray with origin on point that was hit (with a slight add of 0.1 for evading
        // collision inside the sphere), and the direction is the target vector;

        // gets the ambient light applied to the ambient coefficient of the material
        //for the first iteration we do kind of an antialiasing for the color
        if(actual_iteration == iterations){

          for(int i = 0; i > 30; i++){
            //creates a unit vector for the direction of the reflected ray
            // sums the painting rgb with the diffuse coefficient of the material * the recursive Call
            // use_diffuse is 1 if this shader use the diffuse coefficient;
            Ray scattered;
            rec.material->scatter(ray, rec, scattered);
            rgb_to_paint += rec.material->albedo * shade(scattered, scene, actual_iteration - 1);
          }
          //get mean of the colors from this "antialiasing"
          rgb_to_paint /= 30;
        }

        // now, for each pontual light, we have to get the light action on the object
        // for(auto light = scene.lights.begin(); light != scene.lights.end(); light++){
        //
        //   // Here we create a vector in the direction of the light, from the point hit
        //   Vector3 unit_light = unit_vector(light->source - rec.p);
        //
        //   //calculate the cossene with the normal of that point
        //   double cos_light_normal = dot(unit_light, rec.normal);
        //   cos_light_normal = std::max(0.0, cos_light_normal); //cos < 0 means the light did not hit surface
        //
        //     // then we sum the color with the light intensity applyed to the
        //     // diffuse coefficient, applyed to the conssene we found
        //   rgb_to_paint += cos_light_normal * light->intensity * rec.material->k_d * use_diffuse;
        // }


        // sums with the recursive call applied to the diffuse coeficient
        Ray scattered;
        rec.material->scatter(ray, rec, scattered);
        rgb_to_paint += rec.material->albedo * shade(scattered, scene, actual_iteration - 1);

      }
      else{ // the number of iterations hits it's maximum
        rgb_to_paint = RGB(0,0,0); // return black
      }
    }
    else{
      // if the ray hits the background, returns the background color,
      // interpolated at the point that was hit
      rgb_to_paint = interpolate_background(ray, scene.get_background());

    }

    // now we truncate the color to paint to 1, if greater;
    rgb_to_paint.e[0] = std::min(1.d, rgb_to_paint.r());
    rgb_to_paint.e[1] = std::min(1.d, rgb_to_paint.g());
    rgb_to_paint.e[2] = std::min(1.d, rgb_to_paint.b());


    return rgb_to_paint;
  }

  //calls the real shade function with iterations parameter
  RGB Recursive::shade(const Ray &ray, Scene &scene) const {

    return shade(ray, scene, iterations);
  }
#endif
