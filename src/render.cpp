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
using namespace utility;

int main(int argc, char const *argv[])
{
    // int n_cols = 1200;
    // int n_rows = 600;
    //
    // int n_samples = 4;
    //
    // std::ofstream output_file(argv[1], std::ios::out);
    // if (output_file.is_open()){


      //=== Defining our 'camera'
      // Point3 origin(0, 0, 0); // the camera'sbui   origin.
      // Point3 lower_left_corner( -2, -1, -1 ); // lower left corner of the view plane.
      // Vector3 vertical(0, 2, 0); // Vertical dimension of the view plane.
      // Vector3 horizontal( 4, 0, 0 ); // Horizontal dimension of the view plane.
      //
      // Camera cam(origin, lower_left_corner, vertical, horizontal);
      //
      // //creating Scene:
      // std::list< Hitable* > *objects = new std::list< Hitable* >();
      // Background bg;
      // bg.lower_left = RGB(1.d);
      // bg.upper_left = RGB(0.5, 0.7, 1);
      // bg.lower_right = RGB(1.d);
      // bg.upper_right = RGB(0.5, 0.7, 1);
      //
      // RGB ambient_light(0.4);
      //
      // Scene scene(*objects, bg, ambient_light);
      //
      //
      // //filling with Spheres
      // /*Sphere s1(Point3(0,-100.5,-30), 100.d, new Lambertian(RGB(0,1,0)));
      // scene.add_object(&s1);
      // Sphere s2(Point3(0.3, 0, -1), 0.4, new Lambertian(RGB(1,0,0)));
      // scene.add_object(&s2);
      // Sphere s3(Point3(0, 1, -2), 0.6, new Lambertian(RGB(0,0,1)));
      // scene.add_object(&s3);
      // Sphere s4(Point3(-0.4, 0, -3), 0.7, new Lambertian(RGB(1,1,1)));
      // scene.add_object(&s4);*/
      //
      // Sphere s1(Point3(0.0,-100.5f,-1.d), 100.d, new Material(RGB(0.1), RGB(0.4), RGB(1.d), 4));
      // scene.add_object(&s1);
      // Sphere s2(Point3(0.0,0.d,-1.d), 0.4, new Material(RGB(0.1), RGB(0.0,0.3,0.8), RGB(0.9), 32));
      // scene.add_object(&s2);
      // // Sphere s3(Point3(-0.5,0.d,-1.d), 0.4f, new Material(RGB(0.1), RGB(0.0,0.3,0.8), RGB(0.9), 64));
      // // scene.add_object(&s3);
      // //fill scene with pontual lights
      // scene.add_light(Point3(20.d,10.d,5.d), RGB(1.d));
      //
      // Image image(3, 255, n_cols, n_rows, scene, cam, n_samples);
      // image.set_file_name("test");

  if (argc > 1) {
    Parser parser(argv[1]);

    Image image;
    Shader *shader;
    clock_t start = clock();
    if(!parser.parse(image, shader)){
      std::cout << "error parsing" << std::endl;
      return -1;
    }
    // std::vector<int> v;
    // v.push_back(30);
    // v.push_back(45);
    // v.push_back(60);
    // shader = new Cel(v);
    // // std::cout << "scene size: " << image.scene.size() << '\n';
    // if(shader == nullptr){std::cout << "nullptr render" << '\n';}

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


        // Shader *shader = new Standard_shader();
        // Shader *shader = new Depth_map();
        // Shader *shader = new Normal_to_RGB();
        // Shader *shader = new Recursive(40);
        // Shader *shader = new Blinn_Phong(true, true, true, true);//amb, diff, spec, shadow

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
