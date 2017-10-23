#ifndef RAYTRACE_H_
#define RAYTRACE_H_

#include <iostream>
#include <fstream>
#include <random>
#include "Image.h"
#include "Shader.h"
class Raytrace {
	Image image;
	double gamma;
public:
	//Constructors
	Raytrace(Image &img){image = img;}
	//Render fuction
	void render(std::ofstream &image, Shader *&shader);

};
#include "Raytrace.cpp"
#endif
