#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include "PPM.h"
#include "ColorTable.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>

void show_menu( std::ostream& os ) {
  os << "w) set width" << std::endl;
  os << "h) set height" << std::endl;
  os << "x) set minimum x" << std::endl;
  os << "X) set maximum x" << std::endl;
  os << "y) set minimum y" << std::endl;
  os << "Y) set maximum y" << std::endl;
  os << "a) set parameter a" << std::endl;
  os << "b) set parameter b" << std::endl;
  os << "e) set maximum escape value" << std::endl;
  os << "c) calculate all Julia escape values" << std::endl;
  os << "p) assign colors to the PPM using Julia escape values" << std::endl;
  os << "s) save the PPM to file" << std::endl;
  os << "S) show Julia set meta data" << std::endl;
  
  os << "C) calculate all Mandelbrot escape values" << std::endl;
  os << "P) assign colors to the PPM using Mandelbrot escape values" << std::endl;
  os << "M) show Mandelbrot set meta data" << std::endl;
  
  os << "T) resize color table" << std::endl;
  os << "A) assign a color in the color table" << std::endl;
  os << "r) assign a color randomly in the color table" << std::endl;
  os << "g) assign a color gradient in the color table" << std::endl;
  
  os << "q) quit" << std::endl;
}

std::string get_choice( std::ostream& os, std::istream& is ) {
  std::string input;
  os << "Choice? ";
  is >> input;
  return input;
}

void set_width( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  int w, h;
  os << "Pixel Width? ";
  is >> w;
  h = js.getHeight( );
  js.setPixelSize( w, h );
  ms.setPixelSize( w, h );
}

void set_height( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  int w, h;
  os << "Pixel Height? ";
  is >> h;
  w = js.getWidth( );
  js.setPixelSize( w, h );
  ms.setPixelSize( w, h );
}

void set_min_x( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  double x,X,y,Y;
  os << "Min X? ";
  is >> x;
  X = js.getMaxX( );
  y = js.getMinY( );
  Y = js.getMaxY( );
  js.setPlaneSize( x, X, y, Y );
  ms.setPlaneSize( x, X, y, Y );
}

void set_max_x( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  double x,X,y,Y;
  os << "Max X? ";
  is >> X;
  x = js.getMinX( );
  y = js.getMinY( );
  Y = js.getMaxY( );
  js.setPlaneSize( x, X, y, Y );
  ms.setPlaneSize( x, X, y, Y );
}

void set_min_y( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  double x,X,y,Y;
  os << "Min Y? ";
  is >> y;
  x = js.getMinX( );
  X = js.getMaxX( );
  Y = js.getMaxY( );
  js.setPlaneSize( x, X, y, Y );
  ms.setPlaneSize( x, X, y, Y );
}

void set_max_y( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  double x,X,y,Y;
  os << "Max Y? ";
  is >> Y;
  x = js.getMinX( );
  X = js.getMaxX( );
  y = js.getMinY( );
  js.setPlaneSize( x, X, y, Y );
  ms.setPlaneSize( x, X, y, Y );
}

void set_parameter_a( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  double a, b;
  os << "Parameter a? ";
  is >> a;
  b = js.getB( );
  js.setParameters( a, b );
}

void set_parameter_b( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  double a, b;
  os << "Parameter b? ";
  is >> b;
  a = js.getA( );
  js.setParameters( a, b );
}

void set_maximum_escape_value( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  int m;
  os << "Maximum Escape Value? ";
  is >> m;
  js.setMaxEscapeCount( m );
  ms.setMaxEscapeCount( m );
}

void calculate_julia_escape_values( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  js.calculateAllEscapeCounts( );
}

void calculate_mandelbrot_escape_values( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  ms.calculateAllEscapeCounts( );
}

void set_julia_ppm( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  js.setPPM( ppm, ct );
}

void set_mandelbrot_ppm( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  ms.setPPM( ppm, ct );
}

void save_ppm( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  std::string filename;
  os << "Filename? ";
  is >> filename;
  std::ofstream fout( filename, std::ios::binary );
  if( fout ) {
    fout << ppm;
    fout.close( );
  } else {
    os << "Error opening " << filename << std::endl;
  }
}

void show_julia_meta_data( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  os << js.getWidth( ) << "x" << js.getHeight( ) << " "
     << js.getMinX( ) << ":" << js.getMaxX( ) << "," 
     << js.getMinY( ) << ":" << js.getMaxY( ) << " "
     << js.getA( ) << "," << js.getB( ) << " "
     << js.getMaxEscapeCount( ) << std::endl;
}

void show_mandelbrot_meta_data( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  os << ms.getWidth( ) << "x" << ms.getHeight( ) << " "
     << ms.getMinX( ) << ":" << ms.getMaxX( ) << "," 
     << ms.getMinY( ) << ":" << ms.getMaxY( ) << " "
     << ms.getMaxEscapeCount( ) << std::endl;
}

void resize_color_table( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  size_t num_color;
  os << "Number of colors: ";
  is >> num_color;
  ct.setNumberOfColors( num_color );
}

void assign_color( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  size_t position;
  int r,g,b;
  os << "Which position( 0-" << (ct.getNumberOfColors( ) - 1) << " )";
  is >> position;
  os << "Red: ";
  is >> r;
  os << "Green: ";
  is >> g;
  os << "Blue: ";
  is >> b;
  Color c( r, g, b );
  ct[ position ] = c;
}

void assign_random_color( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  size_t position;
  int max;
  os << "Which position( 0-" << (ct.getNumberOfColors( ) - 1) << " )";
  is >> position;
  max = 255;
  ct.setRandomColor( max, position );
}

void assign_color_gradient( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  size_t position1, position2;
  int r1,g1,b1,r2,g2,b2;
  os << "First position( 0-" << (ct.getNumberOfColors( ) - 1) << " )";
  is >> position1;
  os << "First Red: ";
  is >> r1;
  os << "First Green: ";
  is >> g1;
  os << "First Blue: ";
  is >> b1;
  Color c1( r1, g1, b1 );
  
  os << "Second position( " << ( position1+1 ) << "-" << (ct.getNumberOfColors( ) - 1) << " )";
  is >> position2;
  os << "Second Red: ";
  is >> r2;
  os << "Second Green: ";
  is >> g2;
  os << "Second Blue: ";
  is >> b2;
  Color c2( r2, g2, b2 );
  ct.insertGradient( c1, c2, position1, position2 );
}

void quit( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  // do nothing here
}

void comment_line( std::ostream& os, std::istream& is, JuliaSet& js, MandelbrotSet& ms, PPM& ppm, ColorTable& ct ) {
  char c;
  while( is.read( (char *)(&c), 1 ) && c != '\n' ) {
    // throw away the rest of the line of input.
  }
}


const std::map< std::string, void (*)( std::ostream&, std::istream&, JuliaSet&, MandelbrotSet&, PPM&, ColorTable& ) > actions = {
  { "w", set_width },
  { "h", set_height },
  { "x", set_min_x },
  { "X", set_max_x },
  { "y", set_min_y },
  { "Y", set_max_y },
  { "a", set_parameter_a },
  { "b", set_parameter_b },
  { "e", set_maximum_escape_value },
  { "c", calculate_julia_escape_values },
  { "p", set_julia_ppm },
  { "s", save_ppm },
  { "S", show_julia_meta_data },
  
  { "C", calculate_mandelbrot_escape_values },
  { "P", set_mandelbrot_ppm },
  { "M", show_mandelbrot_meta_data },
  
  { "T", resize_color_table },
  { "A", assign_color },
  { "r", assign_random_color },
  { "g", assign_color_gradient },
  { "q", quit },
  
  { "#", comment_line },
};

void take_action( std::ostream& os, std::istream& is,
                  const std::string& choice, JuliaSet& js, MandelbrotSet& ms, 
                  PPM& ppm, ColorTable& ct ) {
  
  std::map< std::string, void (*)( std::ostream&, std::istream&, JuliaSet&, MandelbrotSet&, PPM&, ColorTable& ) >::const_iterator it;
  it = actions.find( choice );
  if( it != actions.end( ) ) {
    it->second( os, is, js, ms, ppm, ct );
  } else {
    os << "Unknown option: " << choice << std::endl;
  }
}

int main( ) {
  /* srand with seeds at 100 mirocsecond (us) resolution */
  std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now( );
  std::chrono::high_resolution_clock::duration   dur = now.time_since_epoch( );
  std::chrono::microseconds us = std::chrono::duration_cast< std::chrono::microseconds > ( dur );
  srand( us.count( ) / 100 );
  
  JuliaSet js;
  MandelbrotSet ms;
  PPM ppm;
  ColorTable ct( 0 );
  std::string choice;
  
  while( choice != "q" && std::cin.good( ) ) {
    show_menu( std::cout );
    choice = get_choice( std::cout, std::cin );
    take_action( std::cout, std::cin, choice, js, ms, ppm, ct );
  }
  
  return 0;
}