#include "Ball.hpp"
#include <cmath>
#include <stdexcept>

Ball::Ball(Point center, Velocity velocity, Color color, double radius, bool isCollide) :
    center_(center),
    velocity_(velocity),
    color_(color), 
    radius_(radius),
    isCollide_(isCollide)
{
    if (radius <= 0) 
    {
        throw std::runtime_error("Величина радиуса не может быть равной нулю или меньше нуля");
    }
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    velocity_ = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return velocity_;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(center_, radius_, color_);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    Ball::center_ = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return center_;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return radius_;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return M_PI * pow(radius_, 3) * 4. / 3.;
}

std::ostream& operator<< (std::ostream& stream, Ball& ball) {
    stream << "center: " << ball.center_ << ", velocity: " << ball.velocity_ << ", color: " << ball.color_;
    return stream;
}

bool Ball::isCollidable() const {
    return isCollide_;
}

