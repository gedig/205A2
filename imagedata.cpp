#include "imagedata.h"

ImageData::ImageData(): maxValue(0), minValue(255),totalValue(0.0f) {
    for(int i = 0; i < 256; i++)
    {
        grey[i] = 0;
        red[i] = 0;
        green[i] = 0;
        blue[i] = 0;
    }
}


ImageData::ImageData(QImage *newImage){
    this->storedImage = newImage->copy();
}

ImageData::~ImageData(){

}

void ImageData::setImage(QImage *tempImage){
    this->storedImage = tempImage->copy();
}

void ImageData::populateArrays(){

    if(this->storedImage.isNull()){
        //Exit.
        return;
    }

    //Scan every pixel and gather the colour data
    for (int i = 0; i < storedImage.width(); i++)
    {
        for(int j = 0; j < storedImage.height(); j++)
        {
            //get pixel at location [i][j]
            QRgb pixel = storedImage.pixel(i,j);

            //Gets the luminosity by weighing how human vision percieves it.
            float value = (float)(.21f*qRed(pixel) + .71f*qGreen(pixel) + .07f*qBlue(pixel));

            this->grey[(int) value]++;
            red[qRed(pixel)]++;
            green[qGreen(pixel)]++;
            blue[qBlue(pixel)]++;
        }
    }

}

bool ImageData::isNull(){
    return storedImage.isNull();
}
