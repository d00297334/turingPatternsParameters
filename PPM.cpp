#include "PPM.h"
#include <vector>
#include <iostream>
#include <cmath>

PPM::PPM() {
    mWidth = 0;
    mHeight = 0;
    mMax_color = 0;
}

int PPM::getWidth( ) const {
    return mWidth;
}

int PPM::getHeight( ) const {
    return mHeight;
}

int PPM::getMaxColorValue( ) const {
    return mMax_color;
}

int PPM::getChannel( const int& row, const int& column, const int& channel ) const {
    if (row < mHeight && row >= 0 && column >= 0 && column < mWidth && channel >=0 && channel < 3) {
        size_t x = (row * mWidth * 3 + column * 3) + channel;
        if (x < mPic.size()) {
            return mPic[x];
        }
    }
    return -1;
}


void PPM::setWidth( const int& width ) {
    if (width >= 0) {
        mWidth = width;
        mPic.resize(mWidth * mHeight * 3);
    }
}


void PPM::setHeight( const int& height ) {
    if (height >= 0) {
        mHeight = height;
        mPic.resize(mWidth * mHeight * 3);
    }
}

void PPM::setMaxColorValue( const int& max_color_value ){
    if (max_color_value >=0 && max_color_value <= 255) {
        mMax_color = max_color_value;
    }
}

void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
    if ( row < mHeight && row >= 0 && column >=0 && column < mWidth && value >=0 && value < 256 && channel >=0 && channel < 3) {
        size_t x = (row * mWidth * 3 + column * 3) + channel;
        if (x < mPic.size()) {
            mPic[x] = value;
        }
    }
}


std::istream &operator>>(std::istream& is, PPM& rhs) {
    char p6;
    char ws;
    is >> p6;
    is >> p6;
    int nums;
    is >> nums;
    rhs.setWidth(nums);
    is >> nums;
    rhs.setHeight(nums);
    is >> nums;
    rhs.setMaxColorValue(nums);
    is >> std::noskipws >> ws;

    unsigned char a;

    for (int i=0; i < rhs.getHeight(); i++ ) {
        for (int j=0; j < rhs.getWidth(); j++) {
            for (int k=0; k < 3; k++) {
                is.read((char*)& a, 1);
                int charToInt = static_cast<int> (a);
                rhs.setChannel(i, j, k, charToInt);
            }
        }
    }
    return is;
}

std::ostream &operator<<(std::ostream& os, const PPM& rhs) {
    int width = rhs.getWidth();
    int height = rhs.getHeight();
    int color = rhs.getMaxColorValue();


    os << "P6" << " " << width << " " << height << " " << color << "\n";
    unsigned char a;
    for (int i=0; i < height; i++ ) {
        for (int j=0; j < width; j++) {
            for (int k=0; k < 3; k++) {
                a = rhs.getChannel(i, j, k);
                os.write((char*)& a, 1);
            }
        }
    } return os;
}

bool PPM::operator==( const PPM& rhs ) const{
    int a = this->getHeight() * this->getWidth();
    int b = rhs.getHeight() * rhs.getWidth();
    return a == b;
}

bool PPM::operator!=( const PPM& rhs ) const{
    int a = this->getHeight() * this->getWidth();
    int b = rhs.getHeight() * rhs.getWidth();
    return a != b;
}

bool PPM::operator<( const PPM& rhs ) const{
    int a = this->getHeight() * this->getWidth();
    int b = rhs.getHeight() * rhs.getWidth();
    return a < b;
}

bool PPM::operator<=( const PPM& rhs ) const {
    int a = this->getHeight() * this->getWidth();
    int b = rhs.getHeight() * rhs.getWidth();
    return a <= b;
}

bool PPM::operator>( const PPM& rhs ) const {
        int a = this->getHeight() * this->getWidth();
    int b = rhs.getHeight() * rhs.getWidth();
    return a > b;
}

bool PPM::operator>=( const PPM& rhs ) const {
    int a = this->getHeight() * this->getWidth();
    int b = rhs.getHeight() * rhs.getWidth();
    return a >= b;
}

PPM& PPM::operator+=( const PPM& rhs ) {
    int a;
    for (int i=0; i < this->mHeight; i++ ) {
        for (int j=0; j < this->mWidth; j++) {
            for (int k=0; k < 3; k++) {
               a = this->getChannel(i, j, k) + rhs.getChannel(i,j,k);
               if (a > 255) {
                    this->setChannel(i, j, k, 255);
                } else if (a < 0) {
                    this->setChannel(i, j, k, 0);
                } else {
                    this->setChannel(i, j, k, a);
                }
            }
        }
    }
    return *this;
}

PPM& PPM::operator-=( const PPM& rhs ) {
    int a;
    for (int i=0; i < this->mHeight; i++ ) {
        for (int j=0; j < this->mWidth; j++) {
            for (int k=0; k < 3; k++) {
               a = this->getChannel(i, j, k) - rhs.getChannel(i, j, k);
               if (a > 255) {
                    this->setChannel(i, j, k, 255);
                } else if (a < 0) {
                    this->setChannel(i, j, k, 0);
                } else {
                    this->setChannel(i, j, k, a);
                }
            }
        }
    }
    return *this;
}

PPM PPM::operator+( const PPM& rhs ) const {
    PPM ppm3 = *this;
    ppm3 += rhs;
    return ppm3;
}

PPM PPM::operator-( const PPM& rhs ) const {
    PPM ppm3 = *this;
    ppm3 -= rhs;
    return ppm3;
}

PPM PPM::operator*( const double& rhs ) const {
    PPM ppm3 = *this;
    ppm3 *= rhs;
    return ppm3;
}

PPM PPM::operator/( const double& rhs ) const {
    PPM ppm3 = *this;
    ppm3 /= rhs;
    return ppm3;
}

PPM& PPM::operator*=( const double& rhs ) {
    int a;
    for (int i=0; i < this->mHeight; i++) {
        for (int j=0; j< this->mWidth; j++) {
            for (int k=0; k < 3; k++) {
                a = this->getChannel(i,j,k);
                double newA = a * rhs;
                if (newA > this->getMaxColorValue()) {
                    this->setChannel(i, j, k, 255);
                } else if (newA < 0) {
                   this->setChannel(i, j, k, 0);
                } else {
                    int doubleToInt = (int)newA;
                    this->setChannel(i, j, k, doubleToInt);
                }
            }
        }
    } return *this;
}


PPM& PPM::operator/=( const double& rhs ) {
    int a;
    for (int i=0; i < this->getHeight(); i++){
        for (int j=0; j < this->getWidth(); j++) {
            for (int k=0; k < 3; k++) {
                a = this->getChannel(i, j, k);
                double newA = a / rhs;
                if (newA > this->getMaxColorValue()) {
                    this->setChannel(i, j, k, 255);
                } else if (newA < 0) {
                    this->setChannel(i, j, k, 0);
                } else {
                    int doubleToInt = (int)newA;
                    this->setChannel(i, j, k, doubleToInt);
                }
            }
        }
    } return *this;
}
