#ifndef CAMERA_H_
#define CAMERA_H_

#include "utility/Vector3.h"
#include "utility/Ray.h"

class Camera{
public:
	// fields
	Vector3 origin;
	Vector3 lower_left_corner;
	Vector3 vertical_axis;
	Vector3 horizontal_axis;

	// Constructors & getters
	Camera(){
		origin = Point3(0);
		lower_left_corner = Point3(0);
		vertical_axis = Vector3(0);
		horizontal_axis = Vector3(0);
	};
	Camera(Point3 origin_, Point3 llc, Vector3 va, Vector3 ha){
		origin = origin_;
		lower_left_corner = llc;
		vertical_axis = va;
		horizontal_axis = ha;
	};


	//Getters
	Vector3 get_lower_left_corner() {return lower_left_corner;};
	Vector3 get_vertical_axis() {return vertical_axis;};
	Vector3 get_horizontal_axis() {return horizontal_axis;};
	Vector3 get_origin() {return origin;};

	//Getting ray shoot from the camera
	Ray get_ray(double u, double v){
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
	}

	Ray get_ray(double row, double col, int n_rows, int n_cols){
		double u = double(col) / double( n_cols ); // walked u% of the horizontal dimension of the view plane.
		double v = double(row) / double( n_rows ); // walked v% of the vertical dimension of the view plane.

		return get_ray(u, v);
	}

};

#endif
