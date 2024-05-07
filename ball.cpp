#include "ball.h"
#include "constants.h"

Ball::Ball(QObject *parent) : QObject(parent), radius(10) {
    position = QPoint(BALL_INIT_POS_X, BALL_INIT_POS_Y);
    velocity = QPoint(BALL_INIT_VELOCITY_X, BALL_INIT_VELOCITY_Y);
}

QRect Ball::getRect() const {
    return QRect(position.x() - radius, position.y() - radius, 2 * radius, 2 * radius);
}

void Ball::move() {
    position += velocity;
}

void Ball::invertXDir() {
    velocity.rx() = -velocity.x();
}

void Ball::invertYDir() {
    velocity.ry() = -velocity.y();
}

void Ball::setPosition(const QPoint &pos) {
    position = pos;
}
