#include "mainwindow.h"

MainWindow::MainWindow()
{
    /*Generates our main widget, and continues to populate it with labels and scrollable areas for our images.*/
    centralWidget = new QWidget;

    setCentralWidget(centralWidget);

    //Sets the boxes with what the images will be.
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    imageLabel2 = new QLabel;
    imageLabel2->setBackgroundRole(QPalette::Base);
    imageLabel2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel2->setScaledContents(true);

    //Sets the area where the images will go.
    imageArea = new QScrollArea;
    imageArea->setBackgroundRole(QPalette::Light);
    imageArea->setWidget(imageLabel);
    imageArea->setWidgetResizable(true);

    imageArea2 = new QScrollArea;
    imageArea2->setBackgroundRole(QPalette::Light);
    imageArea2->setWidget(imageLabel2);
    imageArea2->setWidgetResizable(true);

    leftData = ImageData();
    rightData = ImageData();

    createActions();
    createMenus();

    //Creates a QButtonGroup to keep our addImage buttons in, to send the correct signal to our openFile function.*/
    QButtonGroup *leftRight = new QButtonGroup();

    statsDisplay = new QLabel;
    statsDisplay->setText((QString("Maximum Value = \nMinimum Value = \nAverage Value = ")));

    statsDisplay2 = new QLabel;
    statsDisplay2->setText(QString(("Maximum Value = \nMinimum Value = \nAverage Value = ")));

    //QComboBox is our dropdown menus, containing our various histogram options.
    QComboBox *statsImage1 = new QComboBox();
    statsImage1->addItem("Image1");
    statsImage1->addItem("Greyscale Image1");
    statsImage1->addItem("Red Image1");
    connect(statsImage1, SIGNAL(currentIndexChanged(QString)),this, SLOT(histoCall(QString)));

    QComboBox *statsImage2 = new QComboBox();
    statsImage2->addItem("Image2");
    statsImage2->addItem("Greyscale Image2");
    connect(statsImage2, SIGNAL(currentIndexChanged(QString)),this,SLOT(histoCall(QString)));

    //Creates the buttons that will be used to add Images, replacing cmd-o
    QPushButton *addImage = new QPushButton("Add Image1");
    QPushButton *addImage2 = new QPushButton("Add Image2");

    //Adds our buttons into our button group.
    leftRight->addButton(addImage,1);
    leftRight->addButton(addImage2,0);

    //The buttons are in a button group so they can send their ids to the openFile function so it can tell which image to replace.
    //This connects the buttonGroup to our function slot.
    connect(leftRight, SIGNAL(buttonClicked(int)), this, SLOT(openFile(int)));

    QLabel *imageTitle= new QLabel("Image1");
    QLabel *imageTitle2 = new QLabel("Image2");

    /*Adds our various components into the grid layout. values indicate row, column, rowspan, colspan, allignment*/
    QGridLayout *centralLayout = new QGridLayout;

    centralLayout->addWidget(imageArea, 2,1);
    centralLayout->addWidget(imageArea2,2,8);
    centralLayout->addWidget(imageTitle, 1, 1);
    centralLayout->addWidget(imageTitle2, 1, 8);
    centralLayout->addWidget(addImage,3,1);
    centralLayout->addWidget(addImage2,3,8);
    centralLayout->addWidget(statsDisplay, 4, 1);
    centralLayout->addWidget(statsDisplay2, 4, 8);
    centralLayout->addWidget(statsImage1, 6,1);
    centralLayout->addWidget(statsImage2, 6,8);


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

void MainWindow::histoCall(QString comboItemName)
{
    /*This function recieves the QString from the comboBoxes, then parses it out
        to decide which histogram method needs to be called, and with what image*/
    if(comboItemName.compare(QString("Greyscale Image1"), Qt::CaseInsensitive)==0)
        greyScaleHisto(leftData);
    else if(comboItemName.compare(QString("Greyscale Image2"), Qt::CaseInsensitive)==0)
        greyScaleHisto(rightData);

}


void MainWindow::greyScaleHisto(ImageData histoInfo)
{
    if(histoInfo.isNull())
    {
        QMessageBox::information(this, tr("Warning!"),
                                              tr("Image is Null!"));
        return;
    }

    /*Make this function grab the luminence from every element in histoInfo.grey

    Function must get MaxValue, MinValue, and Average Value, and then graph the luminence histogram*/

}



void MainWindow::openFile(int left){

    filename = QFileDialog::getOpenFileName(this, tr("open file"), "/home",tr("Images (*.png *.tif *.bmp *.jpg)")  );

    //If the filename isn't empty,
    if(!filename.isEmpty()){
        refImage = new QImage(filename);
        if(refImage->isNull()){
            QMessageBox::information(this, tr("Warning!"),
                                                  tr("Cannot load %1.").arg(filename));
            return;
        }

        //Determines whether or not the left or right image should be replaced. Handled from a signal from the button group.
        if(left){
            imageLabel->setPixmap(QPixmap::fromImage(*refImage));
            imageLabel->adjustSize();
            leftData.setImage(refImage);
            leftData.populateArrays();
        }else{
            imageLabel2->setPixmap(QPixmap::fromImage(*refImage));
            imageLabel2->adjustSize();
            rightData.setImage(refImage);
            rightData.populateArrays();
        }
    }
}



