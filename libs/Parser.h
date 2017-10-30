#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include <fstream>

#include "Image.h"

#include "materials/Lambertian.h"
#include "materials/Shiny.h"
#include "materials/Metal.h"
#include "materials/Cartoon.h"
#include "materials/Normal_Material.h"

#include "shaders/Blinn_Phong.h"
#include "shaders/Depth_map.h"
#include "shaders/Normal_to_RGB.h"
#include "shaders/Recursive.h"
#include "shaders/Standard_shader.h"
#include "shaders/Cel.h"

#include "hitables/Sphere.h"

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
