#include "mainwindow.h"
#include "./constants.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(BOARD_WIDTH, BOARD_HEIGHT);
    w.show();
    return a.exec();
}
