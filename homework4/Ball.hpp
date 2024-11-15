#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball 
{
public:
    Ball(Point center, Velocity velocity, Color color, double radius, bool isCollide);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;
public:
    friend std::ostream& operator<< (std::ostream& stream, Ball& bll);
private:
    Velocity velocity_;
    Point center_;
    Color color_;
    double radius_;
    bool isCollide_;
};
