#include "ColorTable.h"

Color::Color()
    :mRed(0), mGreen(0), mBlue(0) {
}

Color::Color( const int& red, const int& green, const int& blue )
    :mRed(red), mGreen(green), mBlue(blue) {

}

int Color::getRed( ) const {
    return this->mRed;
}

int Color::getGreen( ) const {
    return this->mGreen;
}

int Color::getBlue( ) const {
    return this->mBlue;
}
int Color::getChannel( const int& channel ) const {
    if (channel == 0){
        return this->mRed;
    } else if (channel == 1) {
        return this->mGreen;
    } else if (channel == 2) {
        return this->mBlue;
    } else {
        return -1;
    }
}

void Color::setRed( const int& value ) {
    if (value >= 0) {
        this->mRed = value;
    }
}

void Color::setGreen( const int& value ) {
    if (value >= 0) {
        this->mGreen = value;
    }
}

void Color::setBlue( const int& value ) {
    if (value >= 0) {
        this->mBlue = value;
    }
}

void Color::setChannel( const int& channel, const int& value ) {
    if (value >= 0 ) {
        if (channel == 0) {
            this->mRed = value;
        } else if (channel == 1) {
            this->mGreen = value;
        } else if (channel == 2) {
            this->mBlue = value;
        }
    }
}

void Color::invert( const int& max_color_value ) {
    if (max_color_value >= this->mRed && max_color_value >= this->mGreen && max_color_value >= this->mBlue) {
        setRed(max_color_value - this->mRed);
        setGreen(max_color_value - this->mGreen);
        setBlue(max_color_value - this->mBlue);
    }
}


bool Color::operator==( const Color& rhs ) const {
    return (this->getBlue() == rhs.getBlue() && this->getRed() == rhs.getRed() && this->getGreen() == rhs.getGreen());

}




ColorTable::ColorTable( const size_t& num_color )
    :c(num_color) {
        mColors.resize(num_color);

}

size_t ColorTable::getNumberOfColors( ) const {
    return c;
}

void ColorTable::setNumberOfColors( const size_t& num_color ) {
    c = num_color;
    this->mColors.resize(num_color);
}

const Color& ColorTable::operator[]( const int& i ) const {
    if (i >= 0 && i < int(this->mColors.size())) {
        return this->mColors[i];
    }
    const static Color colorObj(-1, -1, -1);
    return colorObj;
}

Color& ColorTable::operator[](const int& i) {
    if (i >= 0 && i < int(this->mColors.size())) {
        return this->mColors[i];
    }
    static Color colorObj(-1, -1, -1);
    static Color master_error(-1,-1,-1);
    colorObj = master_error;
    return colorObj;
}

void ColorTable::setRandomColor( const int& max_color_value, const size_t& position ) {
    int red, green, blue;
    if (position < this->mColors.size() && max_color_value <= 255 && max_color_value >= 0) {
        red = std::rand() % (max_color_value + 1);
        green = std::rand() % (max_color_value + 1);
        blue = std::rand() % (max_color_value + 1);
        mColors[position].setChannel(0, red);
        mColors[position].setChannel(1, green);
        mColors[position].setChannel(2, blue);
    }
}

void ColorTable::insertGradient( const Color& color1, const Color& color2, const size_t& position1, const size_t& position2 ){
    int i;
    if(position1 < position2 && int(position1) >= 0 && int(position2) >= 0 && position1 < mColors.size() && position2 < mColors.size()){
        this->mColors[position1] = color1;
        this->mColors[position2] = color2;

        double d = position2 - position1;

        int red1 = color1.getRed();
        int green1 = color1.getGreen();
        int blue1 = color1.getBlue();

        int red2 = color2.getRed();
        int green2 = color2.getGreen();
        int blue2 = color2.getBlue();


        double red_gap = ((red2 - red1) / d);
        double green_gap = ((green2 - green1) / d);
        double blue_gap = ((blue2 - blue1) / d);

        for (i = 0; i <= d; i++) {
            mColors[position1 + i].setChannel(0, (red1 + i * red_gap));
            mColors[position1 + i].setChannel(1, (green1 + i * green_gap));
            mColors[position1 + i].setChannel(2, (blue1 + i * blue_gap));
        }
    }
}
