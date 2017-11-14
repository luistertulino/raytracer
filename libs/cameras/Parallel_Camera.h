#ifndef _PARALLEL_CAMERA_H_
#define _PARALLEL_CAMERA_H_

#include "../Camera.h"

class Parallel_Camera : public Camera{
  public:
    
    // Constructors
    Parallel_Camera(Point3 look_from, Point3 look_at, Point3 up, Point3 left, 
        Point3 right, Point3 bottom, Point3 top, Vector3 vp_normal = Vector3(0)) : Camera(look_from, look_at, up){
        
        Vector3 direction;
        
        if (vp_normal == Vector3(0) ){//and vp_normal.Y == 0.00 ){and vp_normal.Z == 0.00 ){
            direction = -frame.w;
            is_orthogonal = true;
        }
        else{
            direction = vp_normal;
        }
        
        Vector3 lower_left_corner = origin + left + bottom;
        Vector3 horizontal_axis = origin + right - left;
        Vector3 vertical_axis = origin + top - bottom;

        view_plane = View_Plane(lower_left_corner, horizontal_axis, vertical_axis, direction);
    }

    Ray get_ray(double row, double col, int n_rows, int n_cols){
        Camera::get_ray(row, col, n_rows, n_cols);
    }

    Ray get_ray(double u, double v) const override;
};

Ray Parallel_Camera::get_ray(double u, double v) const{
    Point3 ray_origin = view_plane.lower_left_corner + u*view_plane.horizontal_axis + v*view_plane.vertical_axis;
    Vector3 ray_direction = view_plane.normal;

    return Ray(ray_origin, ray_direction);
}

#endif
