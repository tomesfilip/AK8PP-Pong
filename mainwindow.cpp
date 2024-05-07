#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qtimer.h"
#include <QPainter>

#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), playerScore(0)
    , aiScore(0)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGame);
    timer->start(16);

    ball = new Ball(this);
    player = new Paddle(this);
    ai = new Paddle(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete player;
    delete ai;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawRect(ball->getRect());
    painter.drawRect(player->getRect());
    painter.drawRect(ai->getRect());

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(width() / 4, 50, QString::number(playerScore));
    painter.drawText(3 * width() / 4, 50, QString::number(aiScore));
}

void MainWindow::initBall() {
    ball = new Ball(this);
    ball->setPosition(QPoint(width() / 2, height() / 2));
}

void MainWindow::initPaddles() {
    player = new Paddle(this);
    player->setPosition(QPoint(20, height() / 2 - 30));

    ai = new Paddle(this);
    ai->setPosition(QPoint(width() - 30, height() / 2 - 30));
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (timer->isActive()) {
            timer->stop();
        } else {
            timer->start();
        }
    }
}

void MainWindow::resetGame() {
    initBall();
    initPaddles();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    static QPoint prevPos;

    QPoint pos = event->pos();

    int distance = pos.y() - prevPos.y();
    int maxMovementSpeed = 5;

    if (distance > maxMovementSpeed) {
        distance = maxMovementSpeed;
    } else if (distance < -maxMovementSpeed) {
        distance = -maxMovementSpeed;
    }

    if (pos.x() < width() - 20) {
        int newY = player->getRect().y() + distance;

        if (newY < 0) {
            newY = 0;
        } else if (newY > height() - player->getRect().height()) {
            newY = height() - player->getRect().height();
        }

        player->setPosition(QPoint(20, newY));
    }

    prevPos = pos;
    update();
}

void MainWindow::updateGame() {
    ball->move();

    QPoint aiPaddleCenter = ai->getRect().center();
    QPoint ballCenter = ball->getRect().center();

    if (aiPaddleCenter.y() < ballCenter.y()) {
        ai->setPosition(QPoint(width() - 30, ai->getRect().y() + 2));
    }
    else if (aiPaddleCenter.y() > ballCenter.y()) {
           ai->setPosition(QPoint(width() - 30, ai->getRect().y() - 2));
    }

    QRect ballRect = ball->getRect();
    if (ballRect.top() <= 0 || ballRect.bottom() >= height()) {
        ball->invertYDir();
    }
    if (ballRect.intersects(player->getRect()) || ballRect.intersects(ai->getRect())) {
        ball->invertXDir();
    }
    if (ballRect.left() <= 0) {
        aiScore++;
        resetGame();
    } else if (ballRect.right() >= width()) {
        playerScore++;
        resetGame();
    }

    update();
}
