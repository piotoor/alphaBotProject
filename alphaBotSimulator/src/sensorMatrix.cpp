#include "sensorMatrix.h"

sensorMatrix::sensorMatrix()
{
    //ctor
}

sensorMatrix::~sensorMatrix()
{
    //dtor
}


std::vector<int>& sensorMatrix::getSensorValues()
{
    return this->sensorValues;
}
void sensorMatrix::setTrackImage(std::shared_ptr<sf::Image> trackImage)
{
    this->trackImage = trackImage;
}
