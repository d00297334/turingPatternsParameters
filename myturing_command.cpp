#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include "ColorTable.h"
#include "PPM.h"
#include "ComplexFractal.h"
#include "TuringPattern.h"
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <map>


void set_colorTable_size( ColorTable *colorT, const char *arg) {
    std::stringstream ss;
    size_t size;
    ss.str(arg);
    ss >> size;
    if (ss) {
        colorT->setNumberOfColors(size);
    } else {
        std::cout << "-T arg must be formatted as int" << std::endl;
        std::cout << "-T arg: " << arg << " is invalid. " << std::endl;
    }
}

//-A position:r,g,b // assign (r,g,b) to position
void set_colorTable_rgb_position(ColorTable *colorT, const char *arg) {
    std::stringstream ss;
    int position,r,g,b;
    char c1, c2, c3;
    ss.str(arg);
    ss >> position >> c1 >> r >> c2 >> g >> c3 >> b;
    if (ss && c1 == ':' && c2 == ',' && c3 == ',') {
        colorT->operator[](position).setBlue(b);
        colorT->operator[](position).setRed(r);
        colorT->operator[](position).setGreen(g);
    } else {
        std::cout << "-A arg must be formatted as int:int,int,int" << std::endl;
        std::cout << "-A arg: " << arg << " is invalid. " << std::endl;
    }
}

 // assign random color at position with max as max color value, position:max
void set_colorTable_max_at_position(ColorTable *colorT, const char *arg) {
    std::stringstream ss;
    int position, max;
    char c1;
    ss.str(arg);
    ss >> position >> c1 >> max;
    if (ss && c1 == ':') {
        colorT->setRandomColor(max, position);
    } else {
        std::cout << "-R arg must be formatted as int:int" << std::endl;
        std::cout << "-R arg: " << arg << " is invalid. " << std::endl; 
    }
}

//const Color& color1, const Color& color2, const size_t& position1, const size_t& position2
//-g p1:r1,g1,b1:p2:r2,g2,b2 // assign the color gradient from p1 to p2 with colors (r1,g1,b1)->(r2,g2,b2)
void assign_colorTable_color_gradient(ColorTable *colorT, const char *arg) {
    std::stringstream ss;
    int p1, r1, g1, b1, p2, r2, g2, b2;
    char c1, c2, c3, c4, c5, c6, c7;
    ss.str(arg);
    ss >> p1 >> c1 >> r1 >> c2 >> g1 >> c3 >> b1 >> c4 >> p2 >> c5 >> r2 >> c6 >> g2 >> c7 >> b2;
    if (ss && c1 == ':' && c2 == ',' && c3 == ',' && c4 == ':' && c5 == ':' && c6 == ',' && c7 == ',') {
        
        Color c1;
        c1.setBlue(b1);
        c1.setRed(r1);
        c1.setGreen(g1);
        
        Color c2;
        c2.setBlue(b2);
        c2.setRed(r2);
        c2.setGreen(g2);
        
        colorT->insertGradient(c1, c2, p1, p2);

    } else {
        std::cout << "-g arg must be formatted as int:int,int,int:int:int,int,int" << std::endl;
        std::cout << "-g arg: " << arg << " is invalid. " << std::endl; 
    }

}

//-r minx:maxx,miny:maxy // assign the plane size
void assign_plane_size(ComplexFractal *fractal, const char *arg) {
    std::stringstream ss;
    double minx, maxx, miny, maxy;
    char c1, c2, c3;
    ss.str(arg);
    ss >> minx >> c1 >> maxx >> c2 >> miny >> c3 >> maxy;
    if (ss && c1 == ':' && c2 == ',' && c3 == ':') {
        fractal->setPlaneSize(minx, maxx, miny, maxy);
    } else {
        std::cout << "-r arg must be formatted as double:double,double:double" << std::endl;
        std::cout << "-r arg: " << arg << " is invalid. " << std::endl; 
    }

}

void assign_pixel_size(ComplexFractal *fractal, const char *arg) {
    std::stringstream ss;
    int height, width;
    char c1;
    ss.str(arg);
    ss >> width >> c1 >> height;
    if (ss && c1 == ',') {
        fractal->setPixelSize(width, height);
    } else {
        std::cout << "-p arg must be formatted as int:int" << std::endl;
        std::cout << "-p arg: " << arg << " is invalid. " << std::endl; 
    }
}

void assign_max_escape_value(ComplexFractal *fractal, const char *arg) {
    std::stringstream ss;
    int max;
    ss.str(arg);
    ss >> max;
    if (ss) {
        fractal->setMaxEscapeCount(max);
    } else {
        std::cout << "-m arg must be formatted as int" << std::endl;
        std::cout << "-m arg: " << arg << " is invalid. " << std::endl; 
    }
}

void assign_a_and_b(ComplexFractal *fractal, const char *arg) {
    std::stringstream ss;
    double a, b;
    char c1;
    ss.str(arg);
    ss >> a >> c1 >> b;
    if (ss && c1 == ',') {
        //Dog *dog = dynamic_cast< Dog* >( mammal );
        JuliaSet *js = dynamic_cast< JuliaSet* >(fractal);
        if (js != 0) {
            js->setParameters(a,b);
        } else {
            std::cout << "Julia set a and b parameters could not be set. Does Julia Set exists?" << std::endl;
        }
    } else {
        std::cout << "-a arg must be formatted as double,double" << std::endl;
        std::cout << "-a arg: " << arg << " is invalid. " << std::endl; 
    }
}

void ppm_calculate_set_and_save(ComplexFractal *fractal, ColorTable *colorT, const char *arg) {
    PPM ppm;
    std::stringstream ss;
    std::string filename;
    ss.str(arg);
    ss >> filename;
    if (ss) {
        fractal->calculateAllEscapeCounts();
        fractal->setPPM(ppm, *colorT);
        std::ofstream openfile(filename, std::ios::binary);
        openfile << ppm;
        openfile.close();
    } else {
        std::cout <<"-f arg must be formatted as a string" << std::endl;
    }

}

void assign_turing_pattern_params(ComplexFractal *fractal, const char *arg) {
    std::stringstream ss;
    double dx, dt, alpha, beta, Da, Db;
    char c1, c2, c3, c4, c5;
    ss.str(arg);
    ss >> dx >> c1 >> dt >> c2 >> alpha >> c3 >> beta >> c4 >> Da >> c5 >> Db;
    if (ss && c1 == ','&& c2 == ':' && c3 == ',' && c4 == ':' && c5 == ',') {
        TuringPattern *turing = dynamic_cast<TuringPattern*>(fractal);
        if (turing != 0) {
            turing->setParameters(dx, dt, alpha, beta, Da, Db);
        } else {
            std::cout << "Turing Pattern parameters could not be set. Does Turing Pattern exist?" << std::endl;
        }
    } else {
        std::cout << "-P arg must be formatted as double,double:double,double:double,double" << std::endl;
        std::cout << "-P arg: " << arg << " is invalid. " << std::endl; 
    }
}


void randomly_initialize_turing(ComplexFractal *fractal) {
    TuringPattern *turing = dynamic_cast< TuringPattern* > (fractal);
    if (turing != 0) {
        turing->randomizeValues();
    } else {
        std::cout << "Turing Pattern intialization did not work. Does Turing Pattern exist?" << std::endl;
    }

}

void update_turing_pattern_step_times(ComplexFractal *fractal, const char *arg) {
    std::stringstream ss;
    ss.str(arg);
    int numSteps;
    ss >> numSteps;
    if (ss) {
        TuringPattern *turing = dynamic_cast< TuringPattern* > (fractal);
        if (turing != 0) {
            turing->updateValues(numSteps);
        } else  {
            std::cout << "Turing Pattern step update did not work. Does Turing Pattern exist?" << std::endl;
        }
    } else {
        std::cout << "-U arg must be formatted as int" << std::endl;
        std::cout << "-U arg: " << arg << " is invalid. " << std::endl; 
    }
    
}







int main(int argc, char **argv){

    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now( );
    std::chrono::high_resolution_clock::duration   dur = now.time_since_epoch( );
    std::chrono::microseconds us = std::chrono::duration_cast< std::chrono::microseconds > ( dur );
    std::srand( us.count( ) / 100 );
    std::cout << "Type ./image_command -h or '-?' to show options for this program." << std::endl;



    ComplexFractal *fractal = new JuliaSet( );
    ColorTable *colorT = new ColorTable(16);

    colorT->insertGradient( Color(0,255,0), Color(255,0,255), 0, 15 );
    size_t p1 = 0;
    size_t p2 = colorT->getNumberOfColors() - 1;
    Color color1(0,255,0);
    Color color2(255,0,255);
    
    colorT->insertGradient(color1, color2, p1, p2);



    int c;
    while((c = getopt ( argc, argv, "T:A:R:g:MJr:p:m:a:h?f:Pt:IU:")) != -1 ){
        switch(c) {
            
        case 'T':
            // delete fractal;
            // fractal = new JuliaSet();
            set_colorTable_size( colorT, optarg );
            break;
        case 'A':
            set_colorTable_rgb_position(colorT, optarg );
            break;
        case 'R':
            set_colorTable_max_at_position(colorT, optarg);
            break;  
        case 'g':
            assign_colorTable_color_gradient(colorT, optarg);
            break;
        case 'M':
            delete fractal;
            //*fractal = new MandelbrotSet();
            fractal = new MandelbrotSet();
            break;
        case 'J':
            delete fractal;
            //*fractal = new JuliaSet();
            fractal = new JuliaSet();
            break;
        case 'r':
            assign_plane_size(fractal, optarg);
            break;
        case 'p':
            //-p width,height // assign the pixel size
            assign_pixel_size(fractal, optarg);
            break;
        //-m max // assign max escape value
        case 'm':
            assign_max_escape_value(fractal, optarg);
            break;
        case 'a':
            assign_a_and_b(fractal, optarg);
            break;

        case 'f':
            ppm_calculate_set_and_save(fractal, colorT, optarg);
            break;
        case 'h':
            std::cout << "Use '-T' to set color table size" << std::endl;
            std::cout << "Use '-A' to assign rgb to a position" << std::endl;
            std::cout << "Use '-R' to assign random color at position with max as max color value" << std::endl;
            std::cout << "Use '-g' to assign the color gradient from p1 to p2 with colors (r1,g1,b1)->(r2,g2,b2)" << std::endl;
            std::cout << "Use '-M' to choose a mandelbrot set image" << std::endl;
            std::cout << "Use '-J' to choose a julia set image" << std::endl;
            std::cout << "Use '-r' to assign the plane size" << std::endl;
            std::cout << "Use '-p' to assign the pixel size" << std::endl;
            std::cout << "Use '-m' to assign max escape value" << std::endl;
            std::cout << "Use '-a' to assign the Julia set parameters" << std::endl;
            std::cout << "Use '-f' to calculate escape counts, set a PPM and save to filename.ppm" << std::endl;
            std::cout << "Use '-h' or '-?' to display a help message" << std::endl;
            break;
        case '?':
            std::cout << "Use '-T' to set color table size" << std::endl;
            std::cout << "Use '-A' to assign rgb to a position" << std::endl;
            std::cout << "Use '-R' to assign random color at position with max as max color value" << std::endl;
            std::cout << "Use '-g' to assign the color gradient from p1 to p2 with colors (r1,g1,b1)->(r2,g2,b2)" << std::endl;
            std::cout << "Use '-M' to choose a mandelbrot set image" << std::endl;
            std::cout << "Use '-J' to choose a julia set image" << std::endl;
            std::cout << "Use '-r' to assign the plane size" << std::endl;
            std::cout << "Use '-p' to assign the pixel size" << std::endl;
            std::cout << "Use '-m' to assign max escape value" << std::endl;
            std::cout << "Use '-a' to assign the Julia set parameters" << std::endl;
            std::cout << "Use '-f' to calculate escape counts, set a PPM and save to filename.ppm" << std::endl;
            std::cout << "Use '-h' or '-?' to display a help message" << std::endl;
            break;
        case 'P': 
            delete fractal;
            //*fractal = new TuringPattern();
            fractal = new TuringPattern();
            break;
        case 't':
            assign_turing_pattern_params(fractal, optarg);
            break;
        case 'I':
            randomly_initialize_turing(fractal);
            break;
        case 'U':
            update_turing_pattern_step_times(fractal, optarg);
            break;
              
        default:
            std::cout << "-h|-? // displays this help message" << std::endl;
            return 1;
            break;
        }
    }

    return 0;
}




