
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtOpenGL>
#include <QDebug>
#include <QButtonGroup>
#include <QComboBox>

#include "glwidget.h"
#include "imagedata.h"


QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QSlider;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void openFile(int left);
    void histoCall(QString comboItemName);

private:
    void createActions();
    void createMenus();
    void greyScaleHisto(ImageData *dataRef);
    void colorHisto(ImageData *dataRef, int colour);
    void graphHisto(int workingColor[], bool left);


    /*void greenHisto(int left);
    void blueHisto(int left); */

    QWidget *centralWidget;

    QScrollArea *imageArea;
    QScrollArea *imageArea2;
    QLabel *imageLabel;
    QLabel *imageLabel2;

    GLWidget *histo1;
    GLWidget *histo2;

    QLabel *statsDisplay;
    QLabel *statsDisplay2;

    ImageData leftData;
    ImageData rightData;

    QMenu *fileMenu;

    QAction *exitAct;

    QString filename;


    QImage *refImage;

};

#endif
