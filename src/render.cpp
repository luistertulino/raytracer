#include <iostream>
#include <list>
#include <fstream>
#include <cmath>
#include <limits>
#include <ctime>

#include "../libs/Parser.h"
#include "../libs/Raytrace.h"
#include "../libs/Image.h"
#include "../libs/Shader.h"
#include "../libs/Light.h"
using namespace utility;

int main(int argc, char const *argv[])
{
  
  if (argc > 1) {
    Parser parser(argv[1]);

    Image image;
    Shader *shader;
    clock_t start = clock();
    
    if(!parser.parse(image, shader)){
      std::cout << "error parsing" << std::endl;
      return -1;
    }

    std::cout << "time to parse: " << (double)(clock() - start)/CLOCKS_PER_SEC << " seconds" << std::endl;

    std::string output_file_name = "";
    std::string folder = "";
    if(argc == 2){
      folder = "assets/";
    }
    else if (argc == 3){
      std::string test_images(argv[2]);
      if(test_images == "test"){
        folder = "test_images/";
      }
    }

    output_file_name += folder + image.get_name() + ".ppm";
    std::cout << output_file_name << '\n';

    std::ofstream output_file(output_file_name, std::ios::out);
    if (output_file.is_open()) {
        Raytrace my_raytrace(image);

        start = clock();
        my_raytrace.render(output_file, shader);
        std::cout << "time to render/Raytrace: " << (double)(clock() - start)/CLOCKS_PER_SEC << " seconds" << std::endl;
        output_file.close();
    }
    else{
      std::cout << "could not open output image file" << std::endl;
    }
  }
  else{
    std::cout << "need input file" << '\n';
    return -1;
  }
  return 0;
}
