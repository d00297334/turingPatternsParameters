#ifndef _JULIASET_H_
#define _JULIASET_H_
#include <vector>
#include <cmath>
#include <algorithm>
#include "ComplexFractal.h"



class JuliaSet : public ComplexFractal {
    public:

        JuliaSet();
        virtual ~JuliaSet( );
        double getA() const;
        double getB() const;
        void setParameters( const double& a, const double& b );

        void calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const;
        int calculatePlaneEscapeCount( const double& x0, const double& y0 ) const;
        virtual int calculatePixelEscapeCount( const int& row, const int& column ) const;



    protected:

        double mA;
        double mB;

};





#endif
