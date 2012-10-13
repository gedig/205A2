#include <QtGui>
#include <QtOpenGL>
#include <QDebug>
#include <QButtonGroup>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    /*Generates our main widget, and continues to populate it with labels and scrollable areas for our images.*/
    centralWidget = new QWidget;

    setCentralWidget(centralWidget);


    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    imageLabel2 = new QLabel;
    imageLabel2->setBackgroundRole(QPalette::Base);
    imageLabel2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel2->setScaledContents(true);

    imageArea = new QScrollArea;
    imageArea->setBackgroundRole(QPalette::Light);
    imageArea->setWidget(imageLabel);
    imageArea->setWidgetResizable(true);

    imageArea2 = new QScrollArea;
    imageArea2->setBackgroundRole(QPalette::Light);
    imageArea2->setWidget(imageLabel2);
    imageArea2->setWidgetResizable(true);

    createActions();
    createMenus();




    //Creates a QButtonGroup to keep our addImage buttons in, to send the correct signal to our openFile function.*/
    QButtonGroup *leftRight = new QButtonGroup();

    QPushButton *statsImage1 = new QPushButton("Generate Stats");
    connect(statsImage1, SIGNAL(clicked()), this, SLOT(colorStatistics()));

    QPushButton *addImage = new QPushButton("Add Image1");


    QPushButton *addImage2 = new QPushButton("Add Image2");


    //Adds our buttons into our button group.
    leftRight->addButton(addImage,1);
    leftRight->addButton(addImage2,0);

    connect(leftRight, SIGNAL(buttonClicked(int)), this, SLOT(openFile(int)));

    QLabel *imageTitle= new QLabel("Image1");
    QLabel *imageTitle2 = new QLabel("Image2");

    /*Adds our various components into the grid layout. Ints indicate row, column, rowspan, colspan, allignment*/
    QGridLayout *centralLayout = new QGridLayout;
    centralLayout->addWidget(imageTitle, 1, 1,1,5,Qt::AlignCenter);
    centralLayout->addWidget(imageTitle2, 1, 8,1,5, Qt::AlignCenter);
    /*
    centralLayout->addWidget(imageArea, 2,1,3,5,Qt::AlignHCenter);
    centralLayout->addWidget(imageArea2,2,8,3,5,Qt::AlignHCenter);*/
    centralLayout->addWidget(addImage,4,1,1,3,Qt::AlignHCenter);
    centralLayout->addWidget(addImage2,4,8,1,3,Qt::AlignHCenter);
    centralLayout->addWidget(statsImage1, 3,6,1,2,Qt::AlignHCenter);


    centralWidget->setLayout(centralLayout);


    setWindowTitle(tr("CSC 205 Assignment 2"));
    resize(800, 600);
}




void MainWindow::createActions()
{

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Close);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);

}

void MainWindow::colorStatistics()
{
    if((refImage == NULL) || refImage->isNull())
    {
        QMessageBox::information(this, tr("Warning!"),
                                 tr("Reference Image is Empty"));

        return;
    }

    //Scan every pixel and gather the colour data
    float MaxValue = 0;
    float MinValue = 255;
    float TotalValue = 0;
    for(int i = 0; i < refImage->width(); i++)
    {
        for(int j = 0; j <refImage->height(); j++)
        {

            //Get Pixel at location [i][j]
            QRgb pixel = this->refImage->pixel(i,j);

            float value = (float)(qRed(pixel) + qGreen(pixel) + qBlue(pixel));

            value /= 3.0f;
            if(value > MaxValue)
            {
                MaxValue = value;
            }

            if(value < MinValue)
            {
                MinValue = value;
            }

            TotalValue+= value;
        }
    }
    float AverageValue = TotalValue/(refImage->width()*refImage->height());
    QMessageBox::information(this, tr("Result"),
                             QString("Maximum Value = %1\nMinimum Value = %2\n Average Value = %3")
                             .arg(MaxValue)
                             .arg(MinValue)
                             .arg(AverageValue));
}



void MainWindow::openFile(int left){


    filename = QFileDialog::getOpenFileName(this, tr("open file"), "/home",tr("Images (*.png *.tif *.bmp *.jpg)")  );

    if(!filename.isEmpty()){
        refImage = new QImage(filename);
        if(refImage->isNull()){
            QMessageBox::information(this, tr("Warning!"),
                                                  tr("Cannot load %1.").arg(filename));
            return;
        }
        /*
        imageLabel->setMinimumHeight(refImage->height());
        imageLabel->setMinimumWidth(refImage->width());*/
        if(left){
            imageLabel->setPixmap(QPixmap::fromImage(*refImage));
            imageLabel->adjustSize();
        }else{
            imageLabel2->setPixmap(QPixmap::fromImage(*refImage));
            imageLabel2->adjustSize();
        }
    }


}

