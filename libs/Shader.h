#ifndef SHADER_H_
#define SHADER_H_
#include "utility/Ray.h"
#include "Scene.h"
#include "Light.h"

class Shader{

  public:

//Constructors
    Shader(){
    }

    //Methods

    //virtual, implement in other shaders
    virtual RGB shade(const Ray &ray, Scene &scene) const = 0; //Main function to get color of a point, given a ray and the scene

    RGB interpolate_background(const Ray &ray, const Background &background) const; //Method to interpolate and generate the background

};

RGB Shader::interpolate_background(const Ray &ray, const Background &background) const{
    RGB unit_direction = unit_vector(ray.get_direction());
    double x = 0.5*(unit_direction.x() + 1);

    RGB bottom = (1-x)*background.lower_right + x * background.lower_left;
    RGB top = (1-x)*background.upper_right + x * background.upper_left;

    double y = 0.5*(unit_direction.y() + 1);
    return (1-y) * bottom + y * top;
}

#endif
