#ifndef PLANE_H_
#define PLANE_H_

#include "../Hitable.h"
#include "Triangle.h"

class Plane : public Hitable {
public:
    Point3 origin;
    double height;
    double width;
    Triangle *t1, *t2;
    bool culling;

    Plane () {};
    Plane(Point3 o, double h, double w, Material *mat, bool cull = true) {
        origin = o;

        Point3 p1 = Point3(o.x() + w, o.y(), o.z());
        Point3 p2 = Point3(o.x(), o.y() + h, o.z());
        Point3 p3 = Point3(o.x() + w, o.y() + h, o.z());

        t1 = new Triangle(o, p1, p2, mat, cull);
        t2 = new Triangle(p1, p3, p2, mat, cull);

        material = mat;
    }

    virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) override ;

};

bool Plane::hit(const Ray & r, double t_min, double t_max, hit_record & rec) {

    if(t1->hit(r, t_min, t_max, rec)){
        // std::cout << "hit t1" << '\n';
        return true;
    }
    else if(t2->hit(r, t_min, t_max, rec)){
        // std::cout << "hit t2" << '\n';
        return true;
    }
    else{
        return false;
    }

}

#endif