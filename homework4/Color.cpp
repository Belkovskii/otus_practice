#include "Color.hpp"
#include <iostream>
#include "stdexcept"

Color::Color() = default;

Color::Color(double red, double green, double blue)
    : r{red}, g{green}, b{blue} {}
    
bool Color::validateColor(int param) {
    return param >= 0 && param <= 255;
}

Color::Color(int r, int g, int b) {
    if (!validateColor(r) || !validateColor(g) || !validateColor(b)) {
        throw std::runtime_error("Величина параметра должна быть в диапазоне 0 - 255");
    }
    Color::Color(
        (static_cast<double>(r))/255,
        (static_cast<double>(g))/255,
        (static_cast<double>(b))/255
    );
}

double Color::red() const {
    return r;
}

double Color::green() const {
    return g;
}

double Color::blue() const {
    return b;
}

std::istream& operator>> (std::istream& stream, Color& color) {
    stream >> color.r >> color.g >> color.b;
    return stream;
}

std::ostream& operator<< (std::ostream& stream, const Color& color) {
    stream << "red: " << color.red() << ", green: " << color.green() << ", blue: " << color.blue() << '\n';
    return stream; 
}