#ifndef _TURINGPATTERN_H_
#define _TURINGPATTERN_H_

#include "ComplexFractal.h"
#include <cstdlib>
#include <ctime>


class TuringPattern
    : public ComplexFractal { 

public:
    TuringPattern( );
    double getDx( ) const;
    double getDt( ) const;
    double getAlpha( ) const;
    double getBeta( ) const;
    double getDa( ) const;
    double getDb( ) const;
    virtual void setParameters( const double& dx, const double& dt, const double& alpha, const double& beta, const double& Da, const double& Db );
    double getCurrValue( const int& row, const int& column, const int& species ) const;
    double getPrevValue( const int& row, const int& column, const int& species ) const;
    void setCurrValue( const int& row, const int& column, const int& species, const double& value );
    void setPrevValue( const int& row, const int& column, const int& species, const double& value );
    void swapCurrPrev( );
    void randomizeValues( );
    double calculateDivergence( const int& row, const int& column, const int& species );
    double calculateCurrValue( const int& row, const int& column, const int& species );
    void updateValues( int steps ); 
    double Ra( const double& a, const double& b ) const;
    double Rb( const double& a, const double& b ) const;
    void findMinMaxDifference( );
    virtual void setPixelSize( const int& width, const int& height );
    virtual int calculatePixelEscapeCount( const int& row, const int& column ) const;
    virtual void calculateAllEscapeCounts( );


protected:
    std::vector< std::vector< std::vector< double > > > mData;
    int mCurr, mPrev; 
    double mDx, mDt; 
    double mAlpha, mBeta; 
    double mDa, mDb; 
    double mMinDifference, mMaxDifference; 

};



#endif