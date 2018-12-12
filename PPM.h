#ifndef _PPM_H_
#define _PPM_H_
#include <vector>
#include <string>
#include <fstream>

class PPM {

    public:
        PPM();
        int getWidth( ) const;
        int getHeight( ) const;
        int getMaxColorValue( ) const;
        int getChannel( const int& row, const int& column, const int& channel ) const;
        void setWidth( const int& width );
        void setHeight( const int& height );
        void setMaxColorValue( const int& max_color_value );
        void setChannel( const int& row, const int& column, const int& channel, const int& value );
        bool operator==( const PPM& rhs ) const;
        bool operator!=( const PPM& rhs ) const;
        bool operator<( const PPM& rhs ) const;
        bool operator<=( const PPM& rhs ) const;
        bool operator>( const PPM& rhs ) const;
        bool operator>=( const PPM& rhs ) const;
        PPM& operator+=( const PPM& rhs );
        PPM& operator-=( const PPM& rhs );
        PPM operator+( const PPM& rhs ) const;
        PPM operator-( const PPM& rhs ) const;
        PPM& operator/=( const double& rhs );
        PPM& operator*=( const double& rhs );
        PPM operator*( const double& rhs ) const;
        PPM operator/( const double& rhs ) const;


    protected:
        int mWidth;
        int mHeight;
        int mMax_color;
        std::vector < unsigned char > mPic;

};

std::istream& operator>>( std::istream& is, PPM& rhs );
std::ostream &operator <<(std::ostream& os, const PPM& rhs);




#endif
