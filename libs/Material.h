#ifndef MATERIAL_H_
#define MATERIAL_H_
class Material;
//struct to the point that was hit
struct hit_record {
	double t; //the t at the point
  Point3  p; //the point that was hit
  Vector3 normal; //the normal of the point in relation to the object
	Material *material; //the material that was hit
};
  class Material {

  public:
    RGB albedo; // The coefficient of diffuse reflectance


    //Constructors
    Material(){
      albedo = RGB(0.d); //Black sphere

    }
    Material(RGB rgb){
      albedo = rgb;
    }

    Vector3 reflect(const Vector3 &v_in, const Vector3 &normal) const {
      return v_in - 2*dot(v_in, normal)*normal;
    }

    virtual bool scatter(const Ray &ray_in, const hit_record &rec, Ray &scattered) const = 0;
  };
#endif
