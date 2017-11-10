#ifndef CAMERA_H_
#define CAMERA_H_

#include "utility/Vector3.h"
#include "utility/Ray.h"
#include "View_Plane.h"

#include <cmath>
#define M_PI           3.14159265358979323846

struct Frame{
    Vector3 u;
    Vector3 v;
    Vector3 w;
};

class Camera{
public:
	// fields
	Point3 origin;
	View_Plane view_plane;
    Frame frame;

	// Constructors
	Camera(Point3 look_from, Point3 look_at, Vector3 up){
		frame.w = unit_vector(look_from - look_at);
	    frame.u = unit_vector(cross(up, frame.w));
	    frame.v = unit_vector(cross(frame.w,  frame.u));

		origin = look_from;
	};


	//Getters
	Vector3 get_lower_left_corner() { return view_plane.lower_left_corner; };
	Vector3 get_vertical_axis() { return view_plane.vertical_axis; };
	Vector3 get_horizontal_axis() { return view_plane.horizontal_axis; };
	Vector3 get_origin() { return origin; };

	//Getting ray shoot from the camera
	virtual Ray get_ray(double u, double v) const = 0; /*{
		// Determine the ray's direction, based on the pixel coordinate (col,row).
		// We are mapping (matching) the view plane (vp) to the image.
		// To create a ray we need: (a) an origin, and (b) an end point.
		//
		// (a) The ray's origin is the origin of the camera frame (which is the same as the world's frame).
		//
		// (b) To get the end point of ray we just have to 'walk' from the
		// vp's origin + horizontal displacement (proportional to 'col') +
		// vertical displacement (proportional to 'row').
		Point3 end_point = lower_left_corner + u*horizontal_axis + v*vertical_axis;
		Ray r (origin, unit_vector(end_point - origin));
		return r;
	}*/

	Ray get_ray(double row, double col, int n_rows, int n_cols);

};

Ray Camera::get_ray(double row, double col, int n_rows, int n_cols){
    double u = double(col) / double( n_cols ); // walked u% of the horizontal dimension of the view plane.
    double v = double(row) / double( n_rows ); // walked v% of the vertical dimension of the view plane.

    return get_ray(u, v);
}

#endif
