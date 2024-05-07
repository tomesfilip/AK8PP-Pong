#include "paddle.h"
#include "constants.h"

Paddle::Paddle(QObject *parent) : QObject(parent), size(PADDLE_WIDTH, PADDLE_HEIGHT) {
    position = QPoint();
}

QRect Paddle::getRect() const {
    return QRect(position, size);
}

void Paddle::setPosition(const QPoint &pos) {
    position = pos;
}
