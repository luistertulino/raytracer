#include "Scene.h"
#include "lights/Spotlight.h"

void Scene::add_object(Hitable * object){
	objects.push_back(object);
}

void Scene::add_light(Light * light){
	lights.push_back(light);
}

bool Scene::is_shadow(const Point3 &new_origin, Light *light, Vector3 &light_direction){
    light_direction = unit_vector(light->get_direction(new_origin));
    Ray new_ray(new_origin, light_direction);

    hit_record rec;
    if(hit_first_object(new_ray, rec)){
        return true;
    }

    Spotlight *spotlight = dynamic_cast<Spotlight*>(light);

    if(spotlight != nullptr){

        spotlight->cos_ray_direction = dot(spotlight->direction, -light_direction);
        //double temp_cos = dot(spotlight->direction, -light_direction);

        *light = *spotlight;

        //std::cout << "Temp_cos = " << spotlight->temp_cos << " Angle_cos = " << spotlight->angle_cos << std::endl;
        
        if(spotlight->cos_ray_direction <= spotlight->angle_cos) return true;
    }
    return false;
}

//Check in the list of objects if it hits an object
bool Scene::hit_anything(const Ray & r, double t_min, double t_max, hit_record & rec) const{

	bool hit_anything = false;

	//for each object in the list
	for (auto obj : objects) {
		
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

	for(auto obj : objects){
		
		if(obj->hit(r, min_t, max_t, rec)){
			hit = true;
			break;
		}
	}
	return hit;
}
