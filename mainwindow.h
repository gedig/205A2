
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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
    void colorStatistics();

private:
    void createActions();
    void createMenus();


    QWidget *centralWidget;

    QScrollArea *imageArea;
    QScrollArea *imageArea2;
    QLabel *imageLabel;
    QLabel *imageLabel2;

    QMenu *fileMenu;

    QAction *exitAct;

    QString filename;

    QImage *refImage;
};

#endif
