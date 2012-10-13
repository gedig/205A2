/***CSC 205 Assignment 2: Dylan Gedig
                           V00761947
    This assignment is a histogram generation assignment, where we enact various methods
    to obtain, view, and modify the histograms of 1 or 2 images.***/

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
