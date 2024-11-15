#pragma once
#include "Point.hpp"
#include <cmath>
#include <iostream>

class Velocity {
  public:
    inline Velocity() = default;

    // TODO: комментарии
    inline Velocity(double abs, double angle) {
        const double x = std::cos(angle);
        const double y = std::sin(angle);
        vec = Point{x, y} * abs;
    }

    inline Velocity(const Point& vector) {
        setVector(vector);
    }

    inline void setVector(const Point& vector) {
        vec = vector;
    }

    inline Point vector() const {
        return vec;
    }    

  private:
    Point vec;
};

inline std::istream& operator>> (std::istream& stream, Velocity& velocity)
{
    double x = 0;
    double y = 0;
    stream >> x >> y;
    velocity.setVector(Point{x, y});
    return stream;
}

inline std::ostream& operator<< (std::ostream& stream, const Velocity& velocity)
{
    stream << velocity.vector();
    return stream;
}
