#ifndef IMAGE_H_
#define IMAGE_H_
#include <vector>
#include "Scene.h"
#include "Camera.h"


class Image{

public:
	std::string name;
	int type; //ppm ascii, binary, etc
	int max_color;
	int width, height;
	int antialiasing;
	Scene scene; //background, list of objects, lights and ambient light;
	Camera *camera;

	//Constructors

	Image(){}

	Image(int t, int color, int w, int h, Scene &sce, Camera *&cam, int a = 1){
		width = w;
		height = h;
		scene = sce;
		camera = cam;
		type = t;
		max_color = color;
		antialiasing = a;
	}

	//Getters
	int get_width(){return width;}
	int get_height(){return height;}
	int get_type(){return type;}
	int get_max_color(){return max_color;}
	int get_antialiasing(){return antialiasing;}

	std::string get_name() {return name;}

	Camera* get_camera(){return camera;}
	Scene get_scene(){return scene;}
	Background get_background(){return scene.get_background();}

	void set_file_name(std::string name_){name = name_;}
};

#endif
