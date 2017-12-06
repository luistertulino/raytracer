#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include <fstream>
#include <map>

#include "Image.h"

#include "cameras/Parallel_Camera.h"
#include "cameras/Perspective_Camera.h"

#include "textures/Solid.h"
#include "textures/Checker.h"
#include "textures/Noise.h"

#include "materials/Lambertian.h"
#include "materials/Shiny.h"
#include "materials/Metal.h"
#include "materials/Cartoon.h"
#include "materials/Normal_Material.h"
#include "materials/Dieletric.h"

#include "shaders/Blinn_Phong.h"
#include "shaders/Depth_map.h"
#include "shaders/Normal_to_RGB.h"
#include "shaders/Recursive.h"
#include "shaders/Standard_shader.h"
#include "shaders/Cel.h"

#include "hitables/Sphere.h"
#include "hitables/Triangle.h"

#include "lights/Pontual.h"
#include "lights/Directional.h"
#include "lights/Spotlight.h"

class Parser {
  std::string input_stream;
public:
  explicit Parser(std::string input_name){
    input_stream = input_name;
  }

  bool parse(Image &image, Shader *&shader);

};

#include "Parser.cpp"
#endif
