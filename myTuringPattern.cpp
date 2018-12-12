#include "TuringPattern.h"
#include "ComplexFractal.h"
TuringPattern::TuringPattern( )
    : ComplexFractal(), 
    mCurr( 0 ), mPrev( 1 ), mDx( 1.0 ), mDt( 0.001 ), mAlpha( -0.005 ), mBeta( 10.0 ), mDa( 1.0 ), mDb( 100.0 ), mMinDifference( 1.0e10 ), mMaxDifference( -1.0e10 ){ this->setPixelSize(mWidth,mHeight);
}

double TuringPattern::getDx( ) const{
    return mDx;
}
double TuringPattern::getDt( ) const{
    return mDt;
}
double TuringPattern::getAlpha( ) const{
    return mAlpha;
}
double TuringPattern::getBeta( ) const{
    return mBeta;
}
double TuringPattern::getDa( ) const{
    return mDa;
}
double TuringPattern::getDb( ) const{
    return mDb;
}

double TuringPattern::getCurrValue( const int& row, const int& column, const int& species ) const{
    if(species == 0 || species == 1){
        if(column <= mWidth - 1 && column >= 0 && row <= mHeight - 1 && row >= 0){
            int pos = row * mWidth + column;
            return this->mData[mCurr][species][pos];
        }  
    }
    return 0;
}

double TuringPattern::getPrevValue( const int& row, const int& column, const int& species ) const{
    if(species == 0 || species == 1){
        if(column <= mWidth - 1 && column >= 0 && row <= mHeight - 1 && row >= 0){
            int pos = row * mWidth + column;
            return this->mData[mPrev][species][pos];
        }  
    }
    return 0;
}


void TuringPattern::setParameters( const double& dx, const double& dt, const double& alpha, const double& beta, const double& Da, const double& Db ){
    if(dx > 0 && dt > 0 && alpha > 0 && beta > 0 && Da > 0 && Db > 0){
        mDx = dx;
        mDt = dt;
        mAlpha = alpha;
        mBeta = beta;
        mDa = Da;
        mDb = Db;
    }
}



void TuringPattern::setCurrValue( const int& row, const int& column, const int& species, const double& value ){
    int pos = row * mWidth + column;
    this->mData[mCurr][species][pos] = value;
}

void TuringPattern::setPrevValue( const int& row, const int& column, const int& species, const double& value ){
    int pos = row * mWidth + column;
    this->mData[mPrev][species][pos] = value;
}

void TuringPattern::swapCurrPrev( ){
    int current = mCurr;
    int previous = mPrev;
    mCurr = previous;
    mPrev = current;
}

void TuringPattern::randomizeValues( ){ 
    int big = 1000000;
    int row, column, pos;
    for(pos = 0; pos < 2; pos++){
        for ( row = 0; row < mHeight; row++ ) {
            for ( column = 0; column < mWidth; column++ ) {
                double random = ( ( std::rand( ) % big ) - ( big / 2 ) ) / ( 50.0 * big );
                if (pos == 0) {
                    setCurrValue(row, column, pos, random);
                } else if(pos == 1){
                    setPrevValue(row, column, pos, random);
                }
            }
        }
    }
}

double TuringPattern::calculateDivergence( const int& row, const int& column, const int& species ){
    double a;
    a = -4.0 * getPrevValue(row, column, species) 
    + getPrevValue(((row - 1) + mHeight) % mHeight, column, species) 
    + getPrevValue( row, ((column -1) + mWidth) % mWidth, species)
    + getPrevValue((row + 1) % mHeight, column, species) 
    + getPrevValue( row, (column + 1) % mWidth, species);
    double divergence;
    divergence = a / (mDx * mDx);
    return divergence;

}

double TuringPattern::calculateCurrValue( const int& row, const int& column, const int& species ){ 
    double c;
    if(species == 0){
        c = getPrevValue(row, column, 0) + mDt * mDa * calculateDivergence(row, column, species ) + mDt * Ra(getPrevValue(row, column, 0), getPrevValue( row, column, 1));
        return c;
    }else if(species == 1){
        c = getPrevValue(row, column, 1) + mDt * mDb * calculateDivergence(row, column, species) + mDt * Rb(getPrevValue(row, column, 0), getPrevValue( row, column, 1));
        return c;
    }
    return 0;
    
}

void TuringPattern::updateValues( int steps ){
    int pos, row, column;
    double val1, val2;
    for(pos = 0; pos < steps; pos++){
        swapCurrPrev();
        for ( row = 0; row < mHeight; row++ ) {
            for ( column = 0; column < mWidth; column++ ) { 
                val1 = calculateCurrValue(row, column, 0);
                val2 = calculateCurrValue(row, column, 1);
                setCurrValue(row, column, 0, val1);
                setCurrValue(row, column, 1, val2);
            }
        }
    }
}

double TuringPattern::Ra( const double& a, const double& b ) const{
    // Racurrent(row, column) = Aprevious(row, column) - Aprevious(row, column)*Aprevious(row, column)*Aprevious(row, column) - Bprevious(row, column) + alpha;
    double value;
    value = a - a * a * a - b + mAlpha;
    return value;

}

double TuringPattern::Rb( const double& a, const double& b ) const{
    double value;
    value = (a - b) * mBeta;
    return value;
}

void TuringPattern::findMinMaxDifference( ){
    mMinDifference = 1.0e10;
    mMaxDifference = -1.0e10;
    int i, j;
    double a, b, d;
    for ( i = 0; i < mHeight; i++ ) {
        for ( j = 0; j < mWidth; j++ ) {
            a = getCurrValue(i, j, 0);
            b = getCurrValue(i, j, 1);
            d = a - b;
            if (d < mMinDifference) {
                mMinDifference = d;
            } else if (d > mMaxDifference) {
                mMaxDifference = d;
            }
        }
    }
    

}

void TuringPattern::setPixelSize( const int& width, const int& height ){
    if(width > 0 && height > 0){
        ComplexFractal::setPixelSize(width,height);
        mData.resize(2);
        mData[0].resize(2);
        mData[1].resize(2);
        mData[0][0].resize(width * height);
        mData[0][1].resize(width * height);
        mData[1][0].resize(width * height);
        mData[1][1].resize(width * height);
    }
}

int TuringPattern::calculatePixelEscapeCount( const int& row, const int& column ) const{
    double speciesb = getCurrValue( row, column, 1 );
    double speciesa = getCurrValue( row, column, 0 );
    
    double dist = speciesa - speciesb;
    double subtract = (dist - mMinDifference) / (mMaxDifference - mMinDifference); 
    int escape = 1 + ( mMaxEscapeCount - 2 ) * subtract;
    return escape;
}

void TuringPattern::calculateAllEscapeCounts( ){
    findMinMaxDifference();
    ComplexFractal::calculateAllEscapeCounts();
}

