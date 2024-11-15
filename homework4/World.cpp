#include "World.hpp"
#include "Painter.hpp"
#include <fstream>

static constexpr double timePerTick = 0.001;

World::World(const std::string& worldFilePath) {

    Point ballCenter;
    Velocity ballVelocity;
    Color ballColor;
    double ballRadius;
    bool isCollidable;

    std::ifstream stream(worldFilePath);
    stream >> topLeft >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    while (stream.peek(), stream.good()) {
        stream >> ballCenter >> ballVelocity;
        stream >> ballColor;
        stream >> ballRadius;
        stream >> std::boolalpha >> isCollidable;
        Ball ball{ballCenter, ballVelocity, ballColor, ballRadius, isCollidable};
        balls.push_back(ball);
    }
}

void World::show(Painter& painter) const {

    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
}

void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, ticks);
}