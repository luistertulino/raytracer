#ifndef _VIEW_PLANE_H_
#define _VIEW_PLANE_H_

class View_Plane{
  public:
    Point3 lower_left_corner;
    Vector3 vertical_axis;
    Vector3 horizontal_axis;
    Vector3 normal;

    View_Plane(Vector3 norm = Vector3(0)){
        lower_left_corner = Point3(0);
        vertical_axis = Vector3(0);
        horizontal_axis = Vector3(0);
        normal = norm;
    }

    View_Plane(Point3 &llc, Vector3 &ha, Vector3 &va, Vector3 norm = Vector3(0)){
        lower_left_corner = llc;
        horizontal_axis = ha;
        vertical_axis = va;
        normal = norm;
    }

};

#endif
