#ifndef _MANDELBROTSET_H_
#define _MANDELBROTSET_H_
#include "ComplexFractal.h"


class MandelbrotSet : public ComplexFractal {
    public:
        MandelbrotSet( );
        virtual ~MandelbrotSet( );
        void calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const;
        int calculatePlaneEscapeCount( const double& a, const double& b ) const;
        virtual int calculatePixelEscapeCount( const int& row, const int& column ) const;

    protected:

};

#endif
