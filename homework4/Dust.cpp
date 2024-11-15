#include "Dust.hpp"
#include "Painter.hpp"
#include "Color.hpp"

void Dust::draw(Painter& painter) {
    painter.draw(coordiantes_, 5., Color{66, 70, 255});
}