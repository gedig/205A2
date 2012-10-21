#ifndef AGLWIDGET_H
#define AGLWIDGET_H

#include <QGLWidget>

class Shape;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:

    QPoint lastPos;

};


#endif
