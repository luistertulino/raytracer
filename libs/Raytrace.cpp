#include "Raytrace.h"
#include <cstdio>
#include <cmath>
#include <ctime>

void gamma_correction(RGB &rgb, double gamma = 2.0){
    double r = std::pow(rgb[RGB::R], 1.d/gamma);
    double g = std::pow(rgb[RGB::G], 1.d/gamma);
    double b = std::pow(rgb[RGB::B], 1.d/gamma);
    rgb = RGB(r,g,b);
}

clock_t start;

void show_percentage(int percentage){
    std::cout << "\r" << percentage << "%" << "\t"
                        << "[";
    int line_bar_percentage = percentage/2;
    for (size_t i = 50 - line_bar_percentage; i < 50; i++) {
        std::cout << "=" << std::flush;
    }
    if(line_bar_percentage == 50){
        std::cout << "=" << std::flush;
    }
    else{
        std::cout << ">" << std::flush;
    }
    for (size_t i = line_bar_percentage; i < 50; i++) {
        std::cout << " " << std::flush;
    }
    std::cout << "]\t" << std::flush;
    std::cout << "time: " << (double)(clock() - start)/CLOCKS_PER_SEC << "s" << std::flush;

}

void write_ascii(std::ofstream &output_image, int r, int g, int b){
    output_image << r << " " << g << " " << b << "\n";
}

void write_binary(int r, int g, int b, char buff[], int &i){
    buff[i] = r;
    i++;
    buff[i] = g;
    i++;
    buff[i] = b;
    i++;
}

void Raytrace::render(std::ofstream &output_image, Shader *&shader){
	int n_cols = image.get_width();
	int n_rows = image.get_height();

	Scene scene = image.get_scene();
	int n_samples = image.get_antialiasing();

	char *buff = new char[n_cols * n_rows * 3];
	int i = 0;
		//start writing image file
    output_image << "P" << image.get_type() << "\n"
              	 << n_cols << " " << n_rows << "\n"
              	 << image.get_max_color() << "\n";

	start = clock();
    
    for ( int row = n_rows-1 ; row >= 0 ; --row ) // Y
    {
		int percentage =  int(100.0*double(n_rows-row)/double(n_rows)) ;

		show_percentage(percentage);
		for( int col = 0 ; col < n_cols ; col++ ) // X
      	{
            RGB color(0);
            	//getting antialiasing samples
            for(int sample = 0; sample < n_samples; sample++){
                
                //generate random u and v for antialiasing;
                std::knuth_b random_generator(sample);
                double u = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);
                double v = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);
                
                // generate Ray shoot from camera to point (row + u, col + v)
            	Ray r = image.get_camera()->get_ray(double (row + u), double (col + v), n_rows, n_cols);

                if(shader == nullptr){
            	   std::cout << "nullptr" << '\n';
                }
                // Determine the color of one of the rays, as it travels through the virtual space.
                color += shader->shade( r, scene );

            }
            color /= n_samples; //mean color from antialiasing

            gamma_correction(color);

            int ir = int( 255.99f * color[RGB::R] );
            int ig = int( 255.99f * color[RGB::G] );
            int ib = int( 255.99f * color[RGB::B] );

            if(image.get_type() < 4){
            	write_ascii(output_image, ir, ig, ib);
            }
            else{
            	// std::cout << "i: " << i << '\n';
            	write_binary(ir, ig, ib, buff, i);
            }
        }
    }
    if(image.get_type() > 3){
        output_image.write(buff, n_rows*n_cols*3);
    }
    std::cout << std::endl;

}
