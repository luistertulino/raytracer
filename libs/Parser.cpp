#include "Parser.h"

bool is_blinn_phong, is_depth_map, is_normal_to_rgb, is_recursive, is_standard, is_cel;
bool shadow;
int iterations;

bool string_to_bool(std::string word, bool &result){
    if(word == "true"){
        result = true;
        return true;
    }
    else if(word == "false"){
        result = false;
        return true;
    }
    else{
        return false;
    }
}

void clean_up(std::string &str){
  // Deletes the comments
    std::size_t pos = str.find('#');

    if(pos != std::string::npos){
        str = str.substr(0,pos);
    }

    if(str.back() == '\r'){
        str.pop_back();
    }
}

void split_string(std::string &str, std::string &delimiter, std::vector< std::string > &words){
    // Splits a string based on a delimiter

    int i = 0;
    size_t pos = str.find(delimiter);
    std::string buff = "";

    while (pos != std::string::npos) {
        buff = str.substr(i,pos-i);

        if(!buff.empty()){
            words.push_back(buff);
        }

        i = ++pos;
        pos = str.find(delimiter, pos);

        if (pos == std::string::npos) {
            buff = str.substr(i,str.length());

            if(!buff.empty()){
                words.push_back(buff);
            }
        }
    }
}

// Decodes and verifies the output file format 
bool parse_type(std::vector< std::string > &words, int &type){
    if(words.size() == 3){
        if(words[1] == "="){
            if(words[2] == "ppm"){
                type = 3;
                return true;
            }
        }
    }
    return false;
}

// Decodes the output file encoding
bool parse_codification(std::vector< std::string > &words, int &type){
  if(words.size() == 3){
    if(words[1] == "="){
      if(words[2] == "ascii"){
        return true;
      }
      else if(words[2] == "binary"){
        type += 3;
        return true;
      }
    }
  }
  return false;
}

// Decodes the width of the image
bool parse_width(std::vector< std::string > &words, int &width){
  if(words.size() == 3){
    if(words[1] == "="){
      width = std::stoi(words[2]);
      return true;
    }
  }
  return false;
}

// Decodes the height of the image
bool parse_height(std::vector< std::string > &words, int &height){
  if(words.size() == 3){
    if(words[1] == "="){
      height = std::stoi(words[2]);
      return true;
    }
  }
  return false;
}

// Decodes the maximum color of the image
bool parse_max_color(std::vector< std::string > &words, int &max_color){
  if(words.size() == 3){
    if(words[1] == "="){
      max_color = std::stoi(words[2]);
      return true;
    }
  }
  return false;
}

// Something in the antialiasing
bool parse_antialiasing(std::vector< std::string > &words, int &antialiasing){
  if(words.size() == 3){
    if(words[1] == "="){
      antialiasing = std::stoi(words[2]);
      return true;
    }
  }
  return false;
}


bool parse_material(Material *&material, std::ifstream &input_file, int &line_number){

  RGB ambient, diffuse, specular, albedo;
  RGB shadow_color, outline;

  bool is_lambertian, is_shiny, is_metal, is_normal, is_cartoon;
  int specular_exponent = 0;
  double fuzziness = 1.0;

  is_cartoon = is_normal = is_metal = is_lambertian = is_shiny = false;
  ambient = diffuse = specular = albedo = shadow_color = outline = RGB(0);
  
  std::string line = "";

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delimiter = " ";

      split_string(line, delimiter, words);

      if(words.empty()){continue;}

      if(words[1] == "="){

        // Decodes the material
        if(words[0] == "material"){
          if(is_lambertian or is_shiny or is_metal or is_normal or is_cartoon){
            return false;
          }

          if(words[2] == "lambertian"){
            is_lambertian = true;
          }
          else if(words[2] == "shiny"){
            is_shiny = true;
          }
          else if(words[2] == "metal"){
            is_metal = true;
          }
          else if(words[2] == "normal"){
            is_normal = true;
          }
          else if(words[2] == "cartoon"){
            is_cartoon = true;
          }
          else{
            return false;
          }
        }
        // Decodes the ambient light
        else if(words[0] == "ambient"){

          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            ambient = RGB(r,g,b);
          }
          else{
            return false;
          }
        }
        // Decodes the diffuse reflection
        else if(words[0] == "diffuse"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            diffuse = RGB(r,g,b);
          }
          else{
            return false;
          }
        }
        // Decodes the specular reflection
        else if(words[0] == "specular"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            specular = RGB(r,g,b);
          }
          else{
            return false;
          }
        }
        // Decodes the albedo
        else if(words[0] == "albedo"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            albedo = RGB(r,g,b);
          }
          else{
            return false;
          }
        }
        // Decodes the shadow color
        else if(words[0] == "shadow"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            shadow_color = RGB(r,g,b);
          }
          else{
            return false;
          }
        }
        // Decodes the outline
        else if(words[0] == "outline"){
          if(words.size() == 5){
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            outline = RGB(r,g,b);
          }
          else{
            return false;
          }
        }
        // Decodes the specular exponent
        else if(words[0] == "specular_exponent"){
          if(words.size() == 3){
            specular_exponent = std::stoi(words[2]);
          }
          else{
            return false;
          }
        }
        // Decodes the fuzziness
        else if (words[0] == "fuzziness"){
          if (words.size() == 3) {
            fuzziness = std::stod(words[2]);
          }
          else{
            return false;
          }
        }
        else{
          return false;
        }
      }
      // Creates the appropriate material
      else if(words[0] == "END"){
        if(is_lambertian){
          material = new Lambertian(ambient, albedo);
        }
        else if(is_shiny){
          material = new Shiny(ambient, diffuse, specular, specular_exponent);
        }
        else if (is_metal){
          material = new Metal(albedo, fuzziness);
        }
        else if (is_normal){
          material = new Normal_Material();
        }
        else if (is_cartoon){
          material = new Cartoon(albedo, shadow_color, outline);
        }
        else{
          return false;
        }
        return (words[1] == "MATERIAL") ? true : false;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_object(Hitable *&hitable, std::ifstream &input_file, int &line_number){
  Point3 center;
  Material *material;
  double radius = 1.0;

  bool has_center = false;
  bool has_radius = false;
  bool has_material = false;

  bool is_sphere = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      
      if(words.empty()){continue;}

      if(words[0] == "object"){

        if(words.size() == 3 and words[1] == "="){
          if(words[2] == "sphere"){
            is_sphere = true;
          }
          else{
            return false;
          }
        }

      }

      else if(words[0] == "center"){

        if(words.size() == 5 and words[1] == "="){
          double x = std::stod(words[2]);
          double y = std::stod(words[3]);
          double z = std::stod(words[4]);
          center = Point3(x,y,z);
          has_center = true;
        }

      }
      else if(words[0] == "radius"){
        
        if(words.size() == 3 and words[1] == "="){
          radius = std::stod(words[2]);
          has_radius = true;
        }

      }
      else if(words[0] == "BEGIN"){
        
        if(words.size() == 2){
          
          if(words[1] == "MATERIAL"){
          
            if(!parse_material(material, input_file, line_number)){

              // std::cout << "aqui" << '\n';
              return false;
            }
            
            has_material = true;
          }
          else{
            return false;
          }
        }
        else{
          return false;
        }
      }
      else if(words[0] == "END"){

        if(words.size() == 2){
          
          if(!has_center or !has_material){
            return false;
          }

          if(is_sphere){
          
            if(!has_radius){
              return false;
            }
          
            hitable = new Sphere(center, radius, material);
            return (words[1] == "OBJECT") ? true : false;
          }

        }
      
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_background(Background &background, std::ifstream &input_file, int &line_number){

  bool has_upper_left, has_lower_left;
  bool has_upper_right, has_lower_right;

  has_upper_left = has_upper_right = has_lower_right = has_lower_left = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);

      if(words.empty()){continue;}

      if(words.size() == 5 && words[1] == "="){
        if(words[0] == "lower_left"){
          double r = std::stod(words[2]);
          double g = std::stod(words[3]);
          double b = std::stod(words[4]);
          background.lower_left = RGB(r,g,b);
          has_lower_left = true;
          // std::cout << "aqui" << '\n';
        }
        else if(words[0] == "upper_left"){
          double r = std::stod(words[2]);
          double g = std::stod(words[3]);
          double b = std::stod(words[4]);
          background.upper_left = Point3(r,g,b);
          has_upper_left = true;
        }
        else if(words[0] == "upper_right"){
          double r = std::stod(words[2]);
          double g = std::stod(words[3]);
          double b = std::stod(words[4]);
          background.upper_right = Vector3(r,g,b);
          has_upper_right = true;
        }
        else if(words[0] == "lower_right"){
          double r = std::stod(words[2]);
          double g = std::stod(words[3]);
          double b = std::stod(words[4]);
          background.lower_right = Vector3(r,g,b);
          has_lower_right = true;
        }
      }
      else if(words[0] == "END"){
        if(has_lower_left && has_lower_right && has_upper_right && has_upper_left){
          return (words[1] == "BACKGROUND") ? true : false;
        }
        return false;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_light(Light *&light, std::ifstream &input_file, int &line_number){
  RGB intensity(1);
  Point3 source(0);
  Vector3 direction(0.0);
  double angle = 90.0, attenuation = 0.2;

  bool is_pontual, is_directional, is_spotlight;
  is_pontual = is_directional = is_spotlight = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);
      
      if(words.empty()){continue;}
      
      if(words[1] == "="){

        if (words[0] == "type")
        {          
          if (is_spotlight or is_directional or is_pontual)
          {
            return false;
          }

          if (words[2] == "pontual")
          {
            is_pontual = true;
          }
          else if (words[2] == "directional")
          {
            is_directional = true;
          }
          else if (words[2] == "spotlight")
          {
            is_spotlight = true;
          }
          else{
            return false;
          }
        }
        else if (words[0] == "intensity")
        {
          if (words.size() == 5)
          {
            double r = std::stod(words[2]);
            double g = std::stod(words[3]);
            double b = std::stod(words[4]);
            intensity = RGB(r,g,b);
          }
          else{
            return false;
          }
        }
        else if (words[0] == "source")
        {
          if (words.size() == 5)
          {
            double x = std::stod(words[2]);
            double y = std::stod(words[3]);
            double z = std::stod(words[4]);
            source = Point3(x,y,z);
          }
          else{
            return false;
          }
        }
        else if (words[0] == "direction")
        {
          if (words.size() == 5)
          {
            double x = std::stod(words[2]);
            double y = std::stod(words[3]);
            double z = std::stod(words[4]);
            direction = Vector3(x,y,z);
          }
          else{
            return false;
          }
        }
        else if (words[0] == "angle")
        {
          angle = std::stod(words[2]);
        }
        else if (words[0] == "attenuation")
        {
          attenuation = std::stod(words[2]);
        }
        else{
          return false;
        }
      }
      else if(words[0] == "END" and words[1] == "LIGHT"){

        if(is_pontual){
          light = new Pontual(source, intensity);
        }
        else if (is_directional)
        {
          light = new Directional(direction, intensity);
        }
        else if (is_spotlight)
        {
          light = new Spotlight(source, direction, angle, attenuation, intensity);
        }
        else{
          return false;
        }

        return true;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_scene(Scene &scene, std::ifstream &input_file, int &line_number){

  RGB ambient_light(1);
  scene = Scene();

  std::string line;

  // for (int i = 0; i < line_number i++){std::getline(input_file,line,'\n'); clean_up(line)}

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);

      if(words.empty()){continue;}

      if(words[0] == "BEGIN"){

        if(words[1] == "BACKGROUND"){

          if(!parse_background(scene.background, input_file, line_number)){
            return false;
          }

        }                
        else if(words[1] == "LIGHT"){

          Light *light;

          if(!parse_light(light, input_file, line_number)){
            return false;
          }
          else{
            scene.add_light(light);
          }

        }
        else if(words[1] == "OBJECT"){

          Hitable *object;

          if(!parse_object(object, input_file, line_number)){
            return false;
          }
          else{
            scene.add_object(object);
          }

        }
        else{
          return false;
        }
      }
      else if(words.size() == 5 and words[0] == "ambient_light" and words[1] == "="){

        double r = std::stod(words[2]);
        double g = std::stod(words[3]);
        double b = std::stod(words[4]);
        ambient_light = RGB(r,g,b);
        scene.ambient_light = ambient_light;
      
      }
      else if(words[0] ==  "END"){
        return (words[1] == "SCENE") ? true : false;
      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool parse_camera(Camera *&camera, std::ifstream &input_file, int &line_number){
    Point3 look_from = Point3(0);
    Vector3 look_at, vp_normal, up;
    look_at = vp_normal = Vector3(0);
    up = Vector3(0, 1, 0);

    bool is_perspective = false;
    bool is_parallel = false;

    // parallel arguments
    Point3 left, right, top, bottom;
    left = Point3(-1,0,0);
    right = Point3(1,0,0);
    top = Point3(0,1,0);
    bottom = Point3(0,-1,0);

    // perspective arguments
    double vfov = 90;
    double aspect_ratio = 2;
    double dist_to_focus = 1;
    double focal_opening = 90;


    std::string line;

    while (std::getline(input_file, line, '\n')) {
        
        line_number++;

        clean_up(line);

        if(!line.empty()){

            std::vector< std::string > words;
            std::string delim = " ";

            split_string(line, delim, words);

            if(words.empty()){continue;}

            if(words.size() == 5 && words[1] == "="){

                if(words[0] == "look_from"){
                    double x = std::stod(words[2]);
                    double y = std::stod(words[3]);
                    double z = std::stod(words[4]);
                    
                    look_from = Point3(x,y,z);
                }
                else if(words[0] == "look_at"){
                    double x = std::stod(words[2]);
                    double y = std::stod(words[3]);
                    double z = std::stod(words[4]);
                    look_at = Point3(x,y,z);
                }
                else if(words[0] == "up"){
                    double x = std::stod(words[2]);
                    double y = std::stod(words[3]);
                    double z = std::stod(words[4]);
                    up = Vector3(x,y,z);
                }
                else if(words[0] == "vp_normal"){
                    double x = std::stod(words[2]);
                    double y = std::stod(words[3]);
                    double z = std::stod(words[4]);
                    vp_normal = Vector3(x,y,z);
                }
                else if(words[0] == "left"){
                    double x = std::stod(words[2]);
                    double y = std::stod(words[3]);
                    double z = std::stod(words[4]);
                    left = Vector3(x,y,z);
                }
                else if(words[0] == "right"){
                    double x = std::stod(words[2]);
                    double y = std::stod(words[3]);
                    double z = std::stod(words[4]);
                    right = Vector3(x,y,z);
                }
                else if(words[0] == "top"){
                    double x = std::stod(words[2]);
                    double y = std::stod(words[3]);
                    double z = std::stod(words[4]);
                    top = Vector3(x,y,z);
                }
                else if(words[0] == "bottom"){
                    double x = std::stod(words[2]);
                    double y = std::stod(words[3]);
                    double z = std::stod(words[4]);
                    bottom = Vector3(x,y,z);
                }
            }
            else if (words.size() == 3 && words[1] == "="){

                if(words[0] == "type"){

                    if(is_perspective or is_parallel){
                      std::cerr << "redefinition of camera type" << '\n';
                      return false;
                    }

                    if(words[2] == "perspective"){
                      is_perspective = true;
                    }
                    else if (words[2] == "parallel"){
                      is_parallel = true;
                    }
                    else{
                      return false;
                    }
                }
                else if (words[0] == "vfov"){
                    vfov = std::stod(words[2]);
                }
                else if (words[0] == "dist_to_focus"){
                    dist_to_focus = std::stod(words[2]);
                }
                else if (words[0] == "aspect_ratio"){
                    aspect_ratio = std::stod(words[2]);
                }
                else if (words[0] == "focal_opening"){
                    focal_opening = std::stod(words[2]);
                }
            }
            else if(words[0] == "END"){

                if(is_parallel){
                    camera = new Parallel_Camera(look_from, look_at, up, left, right, bottom, top, vp_normal);
                }
                else if(is_perspective){
                    camera = new Perspective_Camera(look_from, look_at, up, vfov, aspect_ratio, dist_to_focus, focal_opening, vp_normal);
                }
                else{
                    return false;
                }

                return (words[1] == "CAMERA") ? true : false;
            }
            else{
                return false;
            }
        }
    }
    return false;
}

bool parse_shader(Shader *&shader, std::ifstream &input_file, int &line_number){

  bool ambient, diffuse, specular;
  ambient = diffuse = specular = false;
  bool has_shader;
  double max_depth;

  shadow = true;
  iterations = 1;
  max_depth = 1.0;
  has_shader = false;

  std::vector<int> thresholds;
  int outline_threshold = 85;
  is_blinn_phong = is_depth_map = is_normal_to_rgb = is_recursive = is_standard = is_cel = false;

  std::string line;

  while (std::getline(input_file, line, '\n')) {

    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);

      if(words.empty()){continue;}

      if(words.size() == 3 && words[1] == "="){

        if(words[0] == "ambient"){
          
          if(!string_to_bool(words[2], ambient)){
            return false;
          }

        }
        else if(words[0] == "diffuse"){
          
          if(!string_to_bool(words[2], diffuse)){
            return false;
          }

        }
        else if(words[0] == "specular"){
          
          if(!string_to_bool(words[2], specular)){
            return false;
          }

        }
        else if(words[0] == "shadow"){
          
          if(!string_to_bool(words[2], shadow)){
            return false;
          }

        }
        else if(words[0] == "iterations"){
          iterations = std::stoi(words[2]);
        }
        else if(words[0] == "max_depth"){
          max_depth = std::stod(words[2]);
        }
        else if(words[0] == "outline_threshold"){
          outline_threshold = std::stoi(words[2]);
        }
        else if (words[0] == "threshold"){
          thresholds.push_back(std::stoi(words[2]));
        }
        else if(words[0] == "shader"){

          if(is_recursive or is_standard or is_depth_map or is_blinn_phong or is_normal_to_rgb or is_cel){
            return false;
          }
          if(words[2] == "recursive"){
            is_recursive = true;
          }
          else if(words[2] == "normal2rgb"){
            is_normal_to_rgb = true;
          }
          else if(words[2] == "depthmap"){
            is_depth_map = true;
          }
          else if(words[2] == "standard"){
            is_standard = true;
          }
          else if(words[2] == "blinnphong"){
            is_blinn_phong = true;
          }
          else if(words[2] == "cel"){
            is_cel = true;
          }
          else{
            return false;
          }

          has_shader = true;
        }
      }
      else if(words[0] == "END"){
        if (has_shader){
          if(is_standard){
            shader = new Standard_shader();
          }
          if(is_normal_to_rgb){
            shader = new Normal_to_RGB();
          }
          if(is_depth_map){
            shader = new Depth_map(max_depth);
          }
          if(is_recursive){
            shader = new Recursive(iterations);
          }
          if(is_blinn_phong){
            shader = new Blinn_Phong(ambient, diffuse, specular, shadow);
          }
          if(is_cel){
            shader = new Cel(thresholds, outline_threshold);
          }
          return (words[1] == "SHADER") ? true : false;
        }
        else{
          return false;
        }
      }
      else{
        return false;
      }
    }
  }
  return false;
}

void parse_file_name(Image &image, Shader *shader){
  std::string output_file_name = "";
  output_file_name += "{P" + std::to_string(image.get_type())+"}_";
  output_file_name += "{" + std::to_string(image.get_width()) + "x" + std::to_string(image.get_height()) + "}_";
  output_file_name += "{" + std::to_string(image.get_antialiasing()) + "x}_";
  std::string shader_name = "";

  if(is_blinn_phong){
    Blinn_Phong *bp = dynamic_cast<Blinn_Phong*>(shader);

    shader_name += "Blinn_Phong";

    if(bp->use_ambient == 1.0){
      shader_name += "_ambient";
    }
    if(bp->use_diffuse == 1.0){
      shader_name += "_diffuse";
    }
    if(bp->use_specular == 1.0){
      shader_name += "_specular";
    }
    if (shadow) {
      output_file_name += "_shadow";
    }
  }
  else if(is_standard){
    shader_name += "Standard_shader";
  }
  else if(is_depth_map){
    Depth_map *dm = dynamic_cast<Depth_map*>(shader);
    shader_name += "Depth_map_depth_at_" + std::to_string(dm->max_depth);
  }
  else if(is_normal_to_rgb){
    shader_name += "Normal_to_RGB";
  }
  else if(is_recursive){
    shader_name += "Recursive_" + std::to_string(iterations) + "_iterations";
  }
  else if(is_cel){
    Cel *cel = dynamic_cast<Cel*>(shader);
    shader_name += "Cel_outline_at_" + std::to_string(cel->outline_threshold);
  }

  output_file_name += "{" + shader_name + "}_";

  image.set_file_name(output_file_name);

}

bool parse_image(Image &image, Shader *&shader, std::ifstream &input_file, int &line_number){

  int type, max_color, width, height, antialiasing;
  type = max_color = width = height = 0;
  antialiasing = 1;

  bool has_type, has_max_color, has_width, has_height, has_codification;
  has_type = has_max_color = has_width = has_height = has_codification = false;

  Scene scene;
  Camera *camera;

  std::string line;

  while (std::getline(input_file, line, '\n')) {
    // std::cout << "parse_image" << std::endl;
    line_number++;

    clean_up(line);
    // std::cout << line <<std::endl;

    if(!line.empty()){

      std::vector< std::string > words;

      std::string delim = " ";

      split_string(line, delim, words);

      if(words.empty()){continue;}

      if(words[0] == "type"){
      
        if(!parse_type(words, type)){
          return false;
        }
        has_type = true;
      
      }
      else if(words[0] == "codification"){
      
        if(!parse_codification(words, type)){
          return false;
        }
        has_codification = true;
      
      }
      else if(words[0] == "width"){
      
        if(!parse_width(words, width)){
          return false;
        }
        has_width = true;
      
      }
      else if(words[0] == "height"){
      
        if (!parse_height(words, height)) {
          return false;
        }
        has_height = true;
      
      }
      else if(words[0] == "maxcolor"){
        
        if(!parse_max_color(words, max_color)){
          return false;
        }
        has_max_color = true;
      
      }
      else if(words[0] == "antialiasing"){
        if(!parse_antialiasing(words, antialiasing)){
          return false;
        }
      }
      else if(words[0] == "BEGIN"){
        if(words[1] == "SCENE"){

          if(!parse_scene(scene, input_file, line_number)){
            return false;
          }

        }
        else if(words[1] == "SHADER"){

          if(!parse_shader(shader, input_file, line_number)){
            return false;
          }

        }
        else if(words[1] == "CAMERA"){

          if(!parse_camera(camera, input_file, line_number)){
            return false;
          }

        }
      }
      else if(words[0] == "END"){

        if(has_type && has_width && has_height && has_max_color){

          image = Image(type, max_color, width, height, scene, camera, antialiasing);
          parse_file_name(image, shader);

          return (words[1] == "IMAGE") ? true : false;
        }
        else{
          return false;
        }

      }
      else{
        return false;
      }
    }
  }
  return false;
}

bool Parser::parse(Image &image, Shader *&shader){
  std::ifstream input_file(input_stream, std::ios::in);

  if (input_file.is_open()) {

    std::string line = "";
    int line_number = 0;

    while (std::getline(input_file, line, '\n')) {
      line_number++;

      clean_up(line);
      // std::cout << line <<std::endl;

      if(!line.empty()){

        std::vector< std::string > words;

        std::string delim = " ";

        split_string(line, delim, words);

        if(words.empty()){continue;}

        //first non empty line must be BEGIN IMAGE
        if(words[0] == "BEGIN" and words[1] == "IMAGE"){
          // std::cout << line << std::endl;
          if(parse_image(image, shader, input_file, line_number)){
            return true;
            if (shader == nullptr) {
              std::cout << "nullptr parse" << '\n';
            }
          }
          else{
            std::cerr << "Error at line: " << line_number << std::endl;
            return false;
          }

        }
        else{
          std::cerr << "Error at line: " << line_number << std::endl;
          return false;
        }
      }
    }
    return false;
    input_file.close();
  }
  else {
    std::cerr << "Unable to open file\n";
    return false;
  }
};
