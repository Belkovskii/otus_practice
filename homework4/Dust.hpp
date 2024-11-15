#pragma once
#include "Point.hpp"
#include "Painter.hpp"
#include "Velocity.hpp"

class Dust 
{
public: 
    Dust(Point coordintes, Velocity velocity, double existanceTime) :
        coordiantes_(coordintes),
        velocity_(velocity),
        existanceTime_(existanceTime)
    {}
    void draw(Painter& painter);
private:
    Point coordiantes_;
    Velocity velocity_;
    double existanceTime_;
};