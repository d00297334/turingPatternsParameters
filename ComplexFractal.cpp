#include "ComplexFractal.h"


ComplexFractal::ComplexFractal( )
    :mWidth(400), mHeight(300), mMaxEscapeCount(255), mMinX(-2), mMaxX(2), mMinY(-1.5), mMaxY(1.5),  mGap_x(0.01), mGap_y(0.01),  mEscapeCount(120000) {
}

ComplexFractal::~ComplexFractal( ) {

}


int ComplexFractal::getWidth( ) const {
    return mWidth;
}

int ComplexFractal::getHeight( ) const {
    return mHeight;
}

double ComplexFractal::getMinX( ) const {
    return mMinX;
}

double ComplexFractal::getMaxX( ) const {
    return mMaxX;
}

double ComplexFractal::getMinY( ) const {
    return mMinY;
}

double ComplexFractal::getMaxY( ) const {
    return mMaxY;
}

int ComplexFractal::getMaxEscapeCount( ) const {
    return mMaxEscapeCount;
}

void ComplexFractal::setPixelSize( const int& width, const int& height ) {
    if (width >=2 && height >=2) {
        mWidth = width;
        mHeight = height;
        setDeltas(calculateDeltaX(), calculateDeltaY());
        mEscapeCount.resize(width * height);
    }

}


void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y ) {
    if (max_y <= 2 && max_x >= -2 && min_y <= 2 &&min_x <= 2 && min_x >= -2 && min_y >= -2 && max_x <= 2 && max_y >= -2) {
        if (min_x != max_x && min_y != max_y) {
            if (min_x > max_x) {
                mMaxX = min_x;
                mMinX = max_x;
            } else {
               mMaxX = max_x;
               mMinX = min_x;
            }

            if (min_y > max_y) {
                mMaxY = min_y;
                mMinY = max_y;
            }else{
                mMaxY = max_y;
                mMinY = min_y;
            }
            setDeltas(calculateDeltaX(), calculateDeltaY());
        }

    }

}

void ComplexFractal::setMaxEscapeCount( const int& count ) {
    if (count >= 0){
        mMaxEscapeCount = count;
    }
}

double ComplexFractal::getDeltaX( ) const {
    return mGap_x;
}

double ComplexFractal::getDeltaY( ) const {
    return mGap_y;
}

void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y ) {
    if (delta_x >= 0 && delta_y >= 0) {
        mGap_x = delta_x;
        mGap_y = delta_y;
    }
}

double ComplexFractal::calculateDeltaX( ) const {
    double gap_x = (mMaxX - mMinX) / (getWidth() - 1);
    return gap_x;
}

double ComplexFractal::calculateDeltaY( ) const {
    double gap_y = (mMaxY - mMinY) / (getHeight() - 1);
    return gap_y;
}

double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column ) const {
    if (column <= mWidth-1 && column >= 0 ) {
        return mMinX + column * mGap_x;
    }
    return 0;
}

double ComplexFractal::calculatePlaneYFromPixelRow( const int& row ) const {
    if (row <= mHeight -1 && row >= 0) {
        return mMaxY - row * mGap_y;
    }
    return 0;
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const{
    if(column <= mWidth-1 && column >= 0 && row <= mHeight-1 && row >= 0){
        x = calculatePlaneXFromPixelColumn(column);
        y = calculatePlaneYFromPixelRow(row);
    } else{
        x = 0;
        y = 0;
    }
}

const std::vector< int >& ComplexFractal::getEscapeCounts( ) const {
    return this->mEscapeCount;
}

int ComplexFractal::getEscapeCount( const int& row, const int& column ) const {
    if (row <= getHeight()-1 && row >=0 && column <= getWidth()-1 && column >= 0) {
        return mEscapeCount[row*mWidth+column];
    } else {
        return -1;
    }
}


void ComplexFractal::setEscapeCount( const int& row, const int& column, const int& count ) {
    if (row <= getHeight()-1 && row >=0 && column <= getWidth()-1 && column >= 0) {
        if (count >=0 && count <= getMaxEscapeCount()) {
            mEscapeCount[row* mWidth + column] = count;
        }
    }
}


void ComplexFractal::calculateAllEscapeCounts( ) {
    for (int i =0; i < this->mHeight; i++) {
        for (int j =0; j < this->mWidth; j++) {
            int pixel = calculatePixelEscapeCount(i,j);
            setEscapeCount(i,j,pixel);
        }
    }

//loop through all pixels
//calculate escape count
//setEscapeCount to store in vector
}

void ComplexFractal::setPPM( PPM& ppm ) const {
    int red, green, blue;
    ppm.setHeight(this->mHeight);
    ppm.setWidth(this->mWidth);
    ppm.setMaxColorValue(63);
    for (int i =0; i < this->mHeight; i++) {
        for (int j=0; j < this->mWidth; j++){
            int value = mEscapeCount[i * mWidth +j];
            for (int k =0; k <3; k++) {
                if (value == 0) {
                    red = 0;
                    green = 0;
                    blue = 0;
                } else if (value == this->mMaxEscapeCount) {
                    red = 63;
                    green = 31;
                    blue = 31;
                } else if (value % 8 == 0) {
                    red = 63;
                    green = 63;
                    blue = 63;
                } else if (value % 8 == 1) {
                    red = 63;
                    green = 31;
                    blue = 31;
                } else if (value % 8 == 2) {
                    red = 63;
                    green = 63;
                    blue = 31;
                } else if (value % 8 == 3) {
                    red = 31;
                    green = 63;
                    blue = 31;
                } else if (value % 8 == 4) {
                    red = 0;
                    green = 0;
                    blue = 0;
                } else if (value % 8 == 5) {
                    red = 31;
                    green = 63;
                    blue = 63;
                } else if (value % 8 == 6) {
                    red = 31;
                    green = 31;
                    blue = 63;
                } else if (value % 8 == 7) {
                    red = 63;
                    green = 31;
                    blue = 63;
                }
                ppm.setChannel(i,j,0,red);
                ppm.setChannel(i,j,1,green);
                ppm.setChannel(i,j,2,blue);
            }
        }
    }
}


void ComplexFractal::setPPM( PPM& PPM, const ColorTable& colors ) const{
    PPM.setWidth( this->mWidth);
    PPM.setHeight( this->mHeight);
    int count;
    int red, green, blue;

    int mcv = 0;
    for (int i = 0; i <= int(colors.getNumberOfColors()); i++){
        int maxRed = colors[i].getRed();
        int maxGreen = colors[i].getGreen();
        int maxBlue = colors[i].getBlue();
        if(mcv < maxRed){
            mcv = maxRed;
        }
        if(mcv < maxGreen){
            mcv = maxGreen;
        }
        if(mcv < maxBlue){
            mcv = maxBlue;
        }

    }
    PPM.setMaxColorValue( mcv );



    if(int(colors.getNumberOfColors()) >= 3){
        for ( int i = 0; i < PPM.getHeight(); i++ ) {
            for ( int j = 0; j < PPM.getWidth( ); j++ ) {

                count = getEscapeCount( i, j);
                if ( count == mMaxEscapeCount) {
                    red = colors[colors.getNumberOfColors()-1].getRed();
                    green = colors[colors.getNumberOfColors()-1].getGreen();
                    blue = colors[colors.getNumberOfColors()-1].getBlue();

                } else if (count == 0) {
                    red = colors[colors.getNumberOfColors()-2].getRed();
                    green = colors[colors.getNumberOfColors()-2].getGreen();
                    blue = colors[colors.getNumberOfColors()-2].getBlue();

                } else {
                    int index = count % (colors.getNumberOfColors() -2);
                    red = colors[index].getRed();
                    green = colors[index].getGreen();
                    blue = colors[index].getBlue();
                }

                PPM.setChannel(i, j, 0, red);
                PPM.setChannel(i, j, 1, green);
                PPM.setChannel(i, j, 2, blue);
            }
        }
    }
}
