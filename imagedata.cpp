#include "imagedata.h"

ImageData::ImageData(){
    for(int i = 0; i < 256; i++)
    {
        greyArray[i] = 0;
        redArray[i] = 0;
        greenArray[i] = 0;
        blueArray[i] = 0;
    }
}


ImageData::ImageData(int newId){
    this->id = newId;

    for(int i = 0; i < 256; i++)
    {
        greyArray[i] = 0;
        redArray[i] = 0;
        greenArray[i] = 0;
        blueArray[i] = 0;
    }
}

ImageData::~ImageData(){

}

int ImageData::getId(){
    return this->id;
}

void ImageData::setImage(QImage *tempImage){
    this->storedImage = tempImage->copy();
}

QImage ImageData::getImage(){
    return this->storedImage;
}

void ImageData::populateArrays(){

    if(this->storedImage.isNull()){
        //Exit.
        return;
    }
    //Clear arrays before attempting to increment them.
    for(int i = 0; i < 256; i++)
    {
        greyArray[i] = 0;
        redArray[i] = 0;
        greenArray[i] = 0;
        blueArray[i] = 0;
        cumulative[i] = 0;
    }

    //Scan every pixel and gather the colour data
    for (int i = 0; i < storedImage.width(); i++)
    {
        for(int j = 0; j < storedImage.height(); j++)
        {
            //get pixel at location [i][j]
            QRgb pixel = storedImage.pixel(i,j);

            greyArray[qGray(pixel)]++;
            redArray[qRed(pixel)]++;
            greenArray[qGreen(pixel)]++;
            blueArray[qBlue(pixel)]++;
        }
    }
    //Calculates our cumulative luminence array
    cumulative[0] = greyArray[0];
    for(int i = 1; i < 256; i++)
    {
        cumulative[i] = greyArray[i] + cumulative[i-1];
    }

}

void ImageData::getColourArray(int toCopy[256], int colour){
    switch(colour){
        case 0:
            for(int i = 0; i < 256; i++)
            {
                toCopy[i] = this->greyArray[i];
            }
            break;
        case 1:
            for(int i = 0; i < 256; i++)
            {
                toCopy[i] = this->cumulative[i];
            }
            break;
        case 2:
            for(int i = 0; i < 256; i++)
            {
                toCopy[i] = this->redArray[i];
            }
            break;
        case 3:
            for(int i = 0; i < 256; i++)
            {
                toCopy[i] = this->greenArray[i];
            }
            break;
        case 4:
            for(int i = 0; i < 256; i++)
            {
                toCopy[i] = this->blueArray[i];
            }
            break;
    }
}

void ImageData::histoMatch(int cumulativeCopy[]){
    /*Takes the array from another ImageData Object and matches it with our cumulative array.*/
    /*Algorithm and java code found in
        Principles of Digital Image Processing [electronic resource] :
        Fundamental Techniques / by Wilhelm Burger, Mark J. Burge.
        2009
        Books
        ELECTRONIC
        available, Internet Resource */

    float thisCumu[256];
    float otherCumu[256];

    calcCDF(this->cumulative,thisCumu);
    calcCDF(cumulativeCopy,otherCumu);

    int mappingFunction[256];

    //Computes the mapping function.
    for(int i = 0; i < 256; i++)
    {
        int j = 255;
        do{
            mappingFunction[i] = j;
            j--;
        } while (j >=0 && thisCumu[i]<=otherCumu[j]);
    }

    //Translate the image using the matching function.

    //Scan every pixel and gather the colour data, apply the mapping function to the value, and replace original
    for (int i = 0; i < storedImage.width(); i++)
    {
        for(int j = 0; j < storedImage.height(); j++)
        {
            //get pixel at location [i][j]
            QRgb pixel = storedImage.pixel(i,j);
            QColor tempHsv = QColor(pixel);
            QColor converted = tempHsv.fromHsv(tempHsv.hue(),tempHsv.saturation(), mappingFunction[tempHsv.value()]);

            storedImage.setPixel(i,j,converted.rgb());
        }
    }

}

float ImageData::calcCDF(int h[], float cdf[]){
    //Calculate the cumulative distribution function for Histogram h
    int histoSum = 0;
    for(int i = 0; i < 256; i++)
    {
        histoSum+=h[i];
    }

    int histoCumulative = 0;
    for(int i = 0; i < 256; i++)
    {
        histoCumulative+=h[i];
        cdf[i] = (float) histoCumulative/histoSum;
    }
}

bool ImageData::isNull(){
    return this->storedImage.isNull();
}
