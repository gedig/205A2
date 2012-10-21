#include <QtGui>
#include <QtOpenGL>
#include <QImage>
#include <math.h>
#include <stdio.h>
#include <QDir>
#include <QMessageBox>
#include "glwidget.h"


#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

/*  This is our drawing widget, it inherits from OpenGl */


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(256, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(256,150);
}


void GLWidget::initializeGL()
{
    qglClearColor(Qt::white);
}


void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    swapBuffers();
}

void GLWidget::resizeGL(int width, int height)
{

}

