/*** CSC 205 Assignment 2: Histogram Manipulation.
    Dylan Gedig, V00761947

    I apologize in advance for the use of both color and colour. ***/

#include "mainwindow.h"

MainWindow::MainWindow()
    :leftData(1),rightData(0)
{
    /*Generates our main widget, and continues to populate it with labels and scrollable areas for our images.*/
    centralWidget = new QWidget;

    setCentralWidget(centralWidget);

    //Sets the boxes with will become the images
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

    //Creates the QGLWidgets that will have our histograms drawn onto them.
    histo1 = new GLWidget();
    histo1->setMaximumWidth(256);
    histo1->setMinimumWidth(256);
    histo1->setBackgroundRole(QPalette::Base);

    histo2 = new GLWidget();
    histo2->setMaximumWidth(256);
    histo2->setMinimumWidth(256);
    histo2->setBackgroundRole(QPalette::Base);

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
    statsImage1->addItem("Intensity Image1");
    statsImage1->addItem("Cumulative Image1");
    statsImage1->addItem("Red Image1");
    statsImage1->addItem("Green Image1");
    statsImage1->addItem("Blue Image1");
    statsImage1->addItem("Apply Image2 Histogram");
    connect(statsImage1, SIGNAL(currentIndexChanged(QString)),this, SLOT(histoCall(QString)));

    QComboBox *statsImage2 = new QComboBox();
    statsImage2->addItem("Image2");
    statsImage2->addItem("Intensity Image2");
    statsImage2->addItem("Cumulative Image2");
    statsImage2->addItem("Red Image2");
    statsImage2->addItem("Green Image2");
    statsImage2->addItem("Blue Image2");
    statsImage2->addItem("Apply Image1 Histogram");
    connect(statsImage2, SIGNAL(currentIndexChanged(QString)),this,SLOT(histoCall(QString)));

    //Creates the buttons that will be used to add Images, replacing cmd-o
    QPushButton *addImage = new QPushButton("Change Image1");
    QPushButton *addImage2 = new QPushButton("Change Image2");

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
    centralLayout->addWidget(histo1, 5,1);
    centralLayout->addWidget(histo2,5,8);
    centralLayout->addWidget(statsImage1, 6,1);
    centralLayout->addWidget(statsImage2, 6,8);

    centralWidget->setLayout(centralLayout);

    setWindowTitle(tr("CSC 205 Assignment 2 -- Dylan Gedig"));
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
    int cumulativeCopy[256];

    /*This function recieves the QString from the comboBoxes, then parses it out
        to decide which histogram method needs to be called, and with what image*/

    if(comboItemName.compare(QString("Intensity Image1"), Qt::CaseInsensitive)==0)
        colorHisto(&leftData, 0);
    else if(comboItemName.compare(QString("Intensity Image2"), Qt::CaseInsensitive)==0)
        colorHisto(&rightData, 0);
    else if(comboItemName.compare(QString("Cumulative Image1"), Qt::CaseInsensitive)==0)
        colorHisto(&leftData,1);
    else if(comboItemName.compare(QString("Cumulative Image2"), Qt::CaseInsensitive)==0)
        colorHisto(&rightData,1);
    else if(comboItemName.compare(QString("Apply Image2 Histogram"), Qt::CaseInsensitive)==0)
    {
        //Gets the cumulative array from Image2
        rightData.getColourArray(cumulativeCopy, 1);
        leftData.histoMatch(cumulativeCopy);

        //Update the image.
        imageLabel->setPixmap(QPixmap::fromImage(leftData.getImage()));
        imageLabel->adjustSize();
        leftData.populateArrays();
    }
    else if(comboItemName.compare(QString("Apply Image1 Histogram"), Qt::CaseInsensitive)==0)
    {
        //Gets the cumulative array from Image1
        leftData.getColourArray(cumulativeCopy, 1);
        rightData.histoMatch(cumulativeCopy);

        //Update the image.
        imageLabel2->setPixmap(QPixmap::fromImage(rightData.getImage()));
        rightData.populateArrays();
    }
    else if(comboItemName.compare(QString("Red Image1"), Qt::CaseInsensitive)==0)
        colorHisto(&leftData, 2);
    else if(comboItemName.compare(QString("Red Image2"), Qt::CaseInsensitive)==0)
        colorHisto(&rightData, 2);
    else if(comboItemName.compare(QString("Green Image1"), Qt::CaseInsensitive)==0)
        colorHisto(&leftData, 3);
    else if(comboItemName.compare(QString("Green Image2"), Qt::CaseInsensitive)==0)
        colorHisto(&rightData, 3);
    else if(comboItemName.compare(QString("Blue Image1"), Qt::CaseInsensitive)==0)
        colorHisto(&leftData, 4);
    else if(comboItemName.compare(QString("Blue Image2"), Qt::CaseInsensitive)==0)
        colorHisto(&rightData, 4);


}


void MainWindow::colorHisto(ImageData *dataRef, int colour){
    /*This function recieves a pointer to an ImageData object, and an integer denoting which colour
        histogram should be generated. 0 for intensity, 1 for cumulative, and 2 for red, 3 for green, 4 for blue.
        It follows a similar pattern to that of greyScaleHisto, but the r,g, or b value is taken directly
        instead of calculating luminence.*/

    if(dataRef->isNull())
    {
        QMessageBox::information(this, tr("Warning!"),
                                 tr("Image is Null"));
        return;
    }
    int workingArray[256];
    dataRef->getColourArray(workingArray, colour);

    /*This function grabs the colour intensity from every element in the specified array.*/
    int maxValue = 0;
    int minValue = 255;
    int averageValue = 0;

    //Start from the end, get the last populated element in the array
    for(int i = 255; i >=0; i--)
    {
        if(workingArray[i] != 0)
        {
            maxValue = i;
            break;
        }
    }
    //Start from the beginning of the array, stop as soon as you find our first populated (min) value.
    for(int i = 0; i < 256; i++)
    {
        if(workingArray[i] !=0)
        {
            minValue = i;
            break;
        }
    }

    //Loop through the entire array, sum the colour, then divide that by the total amount of pixels for our average intensity.
    for(int i = 0; i < 256; i++)
    {
        averageValue += i*workingArray[i];
    }
    averageValue /= dataRef->getImage().height()*dataRef->getImage().width();

    //Update our fields, then print the Histogram to the screen.
    if(dataRef->getId()==1)
    {
        statsDisplay->setText((tr("Maximum Value = %1 \nMinimum Value = %2 \nAverage Value = %3").arg(maxValue).arg(minValue).arg(averageValue)));
        graphHisto(workingArray, true);
    }else{
        statsDisplay2->setText((tr("Maximum Value = %1 \nMinimum Value = %2 \nAverage Value = %3").arg(maxValue).arg(minValue).arg(averageValue)));
        graphHisto(workingArray,false);
    }

}

void MainWindow::graphHisto(int workingColor[], bool left)
{
    /*This function takes the array that we've selected and prints it into a QGLWidget */

    //determines the max to use as a scale factor for our graph.
    float max = 0;
    for(int i = 0; i < 256; i++)
    {
        if(workingColor[i] > max)
            max = workingColor[i];
    }

    //Declares a new QPainter Object to draw Lines on our Widget.
    QPainter *grapher = new QPainter();

    //Determines which GLWidget to print the histograms on.
    if(left)
    {
        grapher->begin(histo1);
        for(int i = 0; i < 256; i++)
        {
            //Print lines from i,height to i,height-workingColor[i] to histo1
            grapher->drawLine(i,histo1->height(),i,histo1->height()-(float)workingColor[i]/(float)max*150.0f);

        }
    }else{
        grapher->begin(histo2);
        for(int i = 0; i <256; i++)
        {
            //Print lines from i,height, to i,height-workingColour[i] to histo2
            grapher->drawLine(i,histo2->height(),i,histo2->height()-(float)workingColor[i]/max*150.0f);
        }

    }
    grapher->end(); //Destroys our QPainter, freeing up its memory.
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



