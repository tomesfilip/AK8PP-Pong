#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>

#include "paddle.h"
#include "ball.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Paddle *player;
    Paddle *ai;
    Ball *ball;

    int playerScore;
    int aiScore;

    void initBall();
    void initPaddles();
    void resetGame();

private slots:
    void updateGame();
};
#endif // MAINWINDOW_H
