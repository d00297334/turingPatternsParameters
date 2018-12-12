#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet() :ComplexFractal() {
    // get baked fool
}

MandelbrotSet::~MandelbrotSet( ) {

}


int MandelbrotSet::calculatePixelEscapeCount( const int& row, const int& column ) const {
    double y = this->calculatePlaneYFromPixelRow(row);
    double x = this->calculatePlaneXFromPixelColumn(column);
    if (row >=0 && row < this->mHeight && column >=0 && column < this->mWidth) {
        return this->calculatePlaneEscapeCount(x,y);
    } else {
        return -1;
    }
}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const {
    int count = 0;
    double tempx, tempy;
    double x0 = a;
    double y0 = b;
    double dist = sqrt((x0*x0)+(y0*y0));
    if (dist > 2 ) {
        return 0;
    } else  {
        count++;
    }
    while (count < this->mMaxEscapeCount) {
        calculateNextPoint(x0, y0, a, b, tempx, tempy);
        dist = sqrt((tempx*tempx)+(tempy*tempy));
        if (dist > 2) {
            return count;
        } else {
            count++;
            x0 = tempx;
            y0 = tempy;
        }
    }
    return count;

    // set count 0
    // make two temp double variables for iteration
    // make two double variables that are a and b x0,y0
    // while count is less than mMax count
    // calculate next point using x0,y0 variables,  a,b, tempx tempy
    // get distance x1, y1
    // if d is > 2 - return count;
    // else count++, x1 = tempx, y1 = tempy

    // return count






}


void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const {
    x1 = (x0 * x0) - (y0 * y0) + a;
    y1 = (2 * x0 * y0) + b;
}

//Calculate the next escape point after x0, y0 and store in x1, y1,
//using the point a, b. Note that x1 and y1 are return by reference.
