#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QPoint>
#include <QRect>

class Ball: public QObject
{
    Q_OBJECT

public:
    Ball(QObject *parent = nullptr);

    QRect getRect() const;
    void move();
    void invertXDir();
    void invertYDir();
    void setPosition(const QPoint &pos);

private:
    QPoint position;
    QPoint velocity;
    int radius;

};

#endif // BALL_H
