#ifndef PADDLE_H
#define PADDLE_H

#include<QGraphicsRectItem>
#include <QObject>
#include <QKeyEvent>

class Paddle: public QObject
{
    Q_OBJECT

public:
    Paddle(QObject *parent = nullptr);

    QRect getRect() const;
    void setPosition(const QPoint &pos);

private:
    QPoint position;
    QSize size;
};

#endif // PADDLE_H
