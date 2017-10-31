#ifndef SCENE_H_
#define SCENE_H_

#include "Hitable.h"
#include "Light.h"
#include <list>

using namespace utility;

//used for interpolation
struct Background{
	Point3 upper_left;
	Point3 lower_left;
	Point3 upper_right;
	Point3 lower_right;
};

class Scene{
public:

	// fields
	std::list< Hitable* > objects;

	Background background;

	std::list< Light* > lights; //list of pontual lights

	RGB ambient_light; //ambient light, have no source

	//Constructors

	Scene(RGB al = RGB(1,1,1)){
		objects = std::list< Hitable* >();

		background.upper_left = Point3(1.0,1.0,1.0);
		background.lower_left = Point3(1.0,1.0,1.0);
		background.upper_right = Point3(1.0,1.0,1.0);
		background.lower_right = Point3(1.0,1.0,1.0);

		ambient_light = al;
	}

	Scene(std::list< Hitable* > & obj, RGB al = RGB(1,1,1)){
		objects = obj;

		background.upper_left = Point3(1.0,1.0,1.0);
		background.lower_left = Point3(1.0,1.0,1.0);
		background.upper_right = Point3(1.0,1.0,1.0);
		background.lower_right = Point3(1.0,1.0,1.0);

		ambient_light = al;
	}

	Scene(Background & bg, RGB al = RGB(1,1,1)){

		objects = std::list< Hitable* >();

		background = bg;

		ambient_light = al;
	}

	Scene(std::list< Hitable* > & objs, Background & bg, RGB al = RGB(1,1,1)){
		objects = objs;

		background = bg;

		ambient_light = al;
	}

	Scene(std::list< Hitable* > &objs, Background &bg, std::list< Light* > &lights_, RGB al = RGB(1,1,1)){
		objects = objs;

		background = bg;

		lights = lights_;

		ambient_light = al;
	}

	//Getters
	std::list< Hitable* > get_objects() const {return objects;}

	Background get_background() const {return background;}

	RGB get_ambient_light() const {return ambient_light;}

	std::list< Light* > get_lights() const { return lights; }

	//Methods

	unsigned int size() const {return objects.size();} //Number of objects

	void add_object(Hitable * object);

	void add_light(Light * light);

    bool is_shadow(const Point3 &new_origin, Light *light, Vector3 &light_direction);

	bool hit_anything(const Ray & r, double t_min, double t_max, hit_record & rec) const;

	bool hit_first_object(const Ray &r, hit_record & rec) const;
 };


#include "Scene.cpp"
#endif
