#include "Scene.h"

void Scene::add_object(Hitable * object){
	objects.push_back(object);
}

void Scene::add_light(Light &light){
	lights.push_back(light);
}

void Scene::add_light(Point3 source_, RGB intensity_){
	Light light;
	light.source = source_;
	light.intensity = intensity_;

	lights.push_back(light);
}

//Check in the list of objects if it hits an object
bool Scene::hit_anything(const Ray & r, double t_min, double t_max, hit_record & rec) const{

	bool hit_anything = false;

	//for each object in the list
	for (auto i = objects.begin(); i != objects.end(); i++ ) {
		Hitable *obj = *i;

		//test if the object were hit
	  if(obj->hit(r, t_min, t_max, rec)){
	    hit_anything = true;
	    t_max = rec.t; //closest point to the ray origin
	  }

	}
	return hit_anything;
}

bool Scene::hit_first_object(const Ray &r, hit_record & rec) const{
	bool hit = false;

	double min_t = 0.0;
	double max_t = std::numeric_limits<double>::max();

	for(auto i = objects.begin(); i != objects.end(); i++){
		Hitable *obj = *i;

		if(obj->hit(r, min_t, max_t, rec)){
			hit = true;
			break;
		}
	}
	return hit;
}
