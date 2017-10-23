#ifndef HITABLE_H_
#define HITABLE_H_

#include "utility/Ray.h"
#include "Material.h"


class Hitable {
protected:
	  Point3 center; //all objects have a center
		Material *material; //all objects have a material

public:

  Point3 get_center(){return center;}
	Material* get_material(){return material;}

  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) const = 0;
};

#endif
