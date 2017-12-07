#ifndef SPHERE_H_
#define SPHERE_H_

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include "../Hitable.h"
#include "../materials/Lambertian.h"
class Sphere : public Hitable{

  double radius;

public:
    Sphere(){
      center = Point3(0); //create sphere on the center
      radius = 0.d; //sphere with 0 radius
    };
    Sphere(Point3 cen, double r){
      center = cen;
      radius = r;
      material = new Lambertian(); //standard material
    }
    Sphere(Point3 cen, double radius_, Material *mat_){
      center = cen;
      radius = radius_;
      material = mat_;
    }

    double get_radius(){return radius;}

    virtual bool hit( const Ray & r, double t_min, double t_max, hit_record & rec) const;
    virtual void get_u_v(double &u, double &v, const Point3 &p) const;
};

#include "Sphere.cpp"

#endif
