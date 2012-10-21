#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <QImage>
#include <QMessageBox>


class ImageData
{
public:
    ImageData();
    ImageData(int newId);

    ~ImageData();

    int getId();
    void setImage(QImage *tempImage);
    QImage getImage();
    void populateArrays();
    void getColourArray(int toCopy[256], int colour);
    void histoMatch(int cumulativeCopy[]);
    bool isNull();



private:
    QImage storedImage;

    int id;
    int greyArray[256];
    int redArray[256];
    int greenArray[256];
    int blueArray[256];
    int cumulative[256];

    float calcCDF(int h[], float cdf[]);
};

#endif // IMAGEDATA_H
