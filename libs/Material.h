#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Texture.h"

class Material;
//struct to the point that was hit
struct hit_record {
	double t; //the t at the point
  Point3  p; //the point that was hit
  Vector3 normal; //the normal of the point in relation to the object
	Material *material; //the material that was hit
  double u, v; 
};

class Material {

  public:
    //RGB albedo; // The coefficient of diffuse reflectance

    Texture *texture;

    //Constructors
    Material(){}
    /*Material(RGB rgb){
      albedo = rgb;
    }*/

    Material(Texture *t){
      texture = t;
    }

    Vector3 reflect(const Vector3 &v_in, const Vector3 &normal) const {
      return v_in - 2*dot(v_in, normal)*normal;
    }

    virtual bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const = 0;

    RGB color(double u, double v, Point3 &p){
      return texture->value(u, v, p);
    }
  };

#endif
