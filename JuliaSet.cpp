#include "JuliaSet.h"

JuliaSet::JuliaSet()
    :ComplexFractal(), mA(-0.650492), mB(-0.478235) {

}

JuliaSet::~JuliaSet() {

}

double JuliaSet::getA( ) const {
    return mA;
}

double JuliaSet::getB( ) const {
    return mB;
}

void JuliaSet::setParameters( const double& a, const double& b ) {
    if ((a >= -2 && a <= 2) && (b >= -2 && b <= 2)) {
        mA = a;
        mB = b;
    }
}

void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const {
    x1 = (x0 * x0) - (y0 * y0) + getA();
    y1 = (2 * x0 * y0) + getB();
}

int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const {
    double temp_y, temp_x, y1, x1;
    int count = 0;
    temp_y = y0;
    temp_x = x0;
    double d = sqrt((x0 * x0 + y0 * y0));
    if (d > 2) {
        return 0;
    } else {
        count++;
    }

    while (count < this->mMaxEscapeCount) {
        calculateNextPoint(temp_x, temp_y, x1, y1);
        double dist = sqrt((x1*x1)+(y1*y1));
        if (dist > 2) {
            return count;
        } else {
           temp_x = x1;
           temp_y = y1;
           count++;
        }
    }
    return count;
}


// Calculate the number of iterations required for row, column to escape. The return value should be in the range 0 to maximum escape count, inclusive. 0 means immediately escaped. Maximum escape count means never escaped, or escaped on the last step. If row or column is out of range, return -1.

//take row and column
    //convert into x and y
    //calculateplaneescapecount

// int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const {
//     return x0 + y0;
// }

//Calculate escape counts for all pixel locations, storing them.



int JuliaSet::calculatePixelEscapeCount( const int& row, const int& column ) const {
    double y = this->calculatePlaneYFromPixelRow(row);
    double x = this->calculatePlaneXFromPixelColumn(column);
    if (row >=0 && row < this->mHeight && column >=0 && column < this->mWidth) {
        return this->calculatePlaneEscapeCount(x,y);
    } else {
        return -1;
    }
}
