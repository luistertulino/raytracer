#ifndef _PERSPECTIVE_CAMERA_H_
#define _PERSPECTIVE_CAMERA_H_

#include "../Camera.h"
#include <random>

class Perspective_Camera : public Camera{
  public:
    double vertical_fov;
    double aspect_ratio;
    double distance_to_vp;
    double focal_distance;
    double focal_opening;

    Perspective_Camera( Point3 look_from, Vector3 look_at, Vector3 up,
                        double vfov, double aspec, double dist_to_focus, double ap, Vector3 vp_normal = Vector3(0)) : Camera(look_from,look_at,up){

        aspect_ratio = aspec;
        vertical_fov = vfov;
        focal_distance = dist_to_focus;
        focal_opening = ap;
        Point3 vp_center = look_at - look_from;
        distance_to_vp = vp_center.length();

        double theta = vfov * M_PI / 180;
        double half_height = distance_to_vp * std::tan(theta/2);
        double half_width = aspect_ratio * half_height;

        Vector3 direction = vp_normal;
        if (vp_normal == Vector3(0)){
            direction = unit_vector(-frame.w);
        }

        Vector3 lower_left_corner = origin + direction*distance_to_vp - half_width*frame.u - half_height*frame.v;
        Vector3 horizontal_axis = 2 * half_width  * frame.u;
        Vector3 vertical_axis = 2 * half_height * frame.v;

        view_plane = View_Plane(lower_left_corner, horizontal_axis, vertical_axis, direction);
    }

    Ray get_ray(double row, double col, int n_rows, int n_cols){
        Camera::get_ray(row, col, n_rows, n_cols);
    }

    Ray get_ray(double u, double v) const override;
};

Ray Perspective_Camera::get_ray(double u, double v) const {
    Vector3 target = view_plane.lower_left_corner + u*view_plane.horizontal_axis + v*view_plane.vertical_axis;
    target = target - origin;

    Ray r(origin, unit_vector(target));

    if(focal_opening > 0){
        Vector3 sample = (random_vector_in_unit_disk()) * focal_opening;

        Point3 focus_point = r.point_at(focal_distance);

        Point3 new_origin = origin + (sample.x() * frame.u) + (sample.y() * frame.v);
        target = focus_point - new_origin;

        r = Ray(new_origin, unit_vector(target));
    }
    return r;
}

#endif
