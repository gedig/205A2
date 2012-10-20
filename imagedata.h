#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <QImage>
#include <QMessageBox>


class ImageData
{
public:
    ImageData();
    ImageData(QImage *newImage);

    ~ImageData();

    void setImage(QImage *tempImage);
    void populateArrays();
    bool isNull();


private:
    QImage storedImage;
    int grey[256];
    int red[256];
    int green[256];
    int blue[256];

    int maxValue;
    int minValue;
    float totalValue;
};

#endif // IMAGEDATA_H
