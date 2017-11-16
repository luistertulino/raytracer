#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#define EPSILON 0.0001

#include "../Hitable.h"

class Triangle : public Hitable{
  public:

    Point3 v0, v1, v2, origin;
    Vector3 edge_1, edge_2, normal;
    bool culling;

    void make_edges_and_etc(Point3 &v0_, Point3 &v1_, Point3 &v2_, bool cull){
        edge_1 = v1 - v0;
        edge_2 = v2 - v0;

        normal = unit_vector(cross(edge_1, edge_2));

        culling = cull;
    }

    Triangle(bool cull = true){
        origin = v0 = v1 = v2 = Point3(0);

        make_edges_and_etc(v0, v1, v2, cull);
    }

    Triangle(Point3 &v0_, Point3 &v1_, Point3 &v2_, bool cull = true){
        origin = v0 = v0_;
        v1 = v1_;
        v2 = v2_;

        make_edges_and_etc(v0, v1, v2, cull);
    }

    Triangle(Point3 &v0_, Point3 &v1_, Point3 &v2_, Material* mat, bool cull = true){
        origin = v0 = v0_;
        v1 = v1_;
        v2 = v2_;

        make_edges_and_etc(v0, v1, v2, cull);

        material = mat;
    }

    virtual bool hit(const Ray &r, double t_min, double t_max, hit_record &rec) const;

};

bool Triangle::hit(const Ray &r, double t_min, double t_max, hit_record &rec) const {

    double t;

    Vector3 P = cross(r.get_direction(), edge_2); // P = D X E_2

    double det = dot(edge_1, P);

    if(culling){
        if(det < EPSILON) return false;

        Vector3 T = r.get_origin() - v0; // T = O - V0

        double u = dot(T, P);
        if(u < 0.0 or u > det) return false;

        Vector3 Q = cross(T, edge_1); // Q = T X E1

        double v = dot(r.get_direction(), Q);
        if(v < 0.0 or u > det) return false;

        t = dot(edge_2, Q);

        double inv_det = 1/det;
        t *= inv_det; u *= inv_det; v *= inv_det;
    }
    else{
        if(det > -EPSILON and det < EPSILON) return false;

        double inv_det = 1/det;

        Vector3 T = r.get_origin() - v0; // T = O - V0

        double u = dot(T, P) * inv_det;
        if(u < 0.0 or u > 1.0) return false;

        Vector3 Q = cross(T, edge_1); // Q = T X E1

        double v = dot(r.get_direction(), Q) * inv_det;
        if(v < 0.0 or u + v > 1.0) return false;

        t = dot(edge_2, Q) * inv_det;

        if(t < EPSILON) return false;
    }
    /*if(t > t_max) return false;

    if(t < t_min){
		t_min = t;
		rec.t = t;	
		rec.p = r.point_at(t);
		rec.normal = normal;
		rec.material = material;
		return true;
	}

	return false;*/

    if(t < t_max and t > t_min){
        rec.t = t;
        rec.p = r.point_at(t);
        rec.material = material;
        rec.normal = normal;//unit_vector(cross(edge_1, edge_2));
    }

    return true;
}

#endif 


