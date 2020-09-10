#include "sensorMatrix.h"
#include <cmath>
#include <iostream>
sensorMatrix::sensorMatrix()
{
    //ctor
}

sensorMatrix::~sensorMatrix()
{
    //dtor
}


std::vector<int> sensorMatrix::getSensorValues() const
{
    return this->sensorValues;
}

void sensorMatrix::setTrackImage(std::shared_ptr<sf::Image> trackImage)
{
    this->trackImage = trackImage;
}

void sensorMatrix::setCarSprite(std::shared_ptr<sf::Sprite> carSprite)
{
    this->carSprite = carSprite;
}

void sensorMatrix::calculateSensorValues()
{
    calculateSensorCenters();
    const float carSpriteWidth = carSprite->getTexture()->getSize().x * carSprite->getScale().x;
    const float sensorSide = 0.075f * carSpriteWidth;
    const float halfSensorSide = sensorSide / 2.0f;

    for (int i = 0; i < 5; ++i) {
        std:: cout << sensorCenters[i].first << " " << sensorCenters[i].second << std::endl;
        float centX = sensorCenters[i].first;
        float centY = sensorCenters[i].second;
        sensorValues[i] = 0;
        int total = 0;
        for (float x = centX - halfSensorSide; x <= centX + halfSensorSide; x += 1.0f) {
            for (float y = centY - halfSensorSide; y <= centY + halfSensorSide; y += 1.0f) {
                sf::Color trackPixel = trackImage->getPixel(x, y);
                sensorValues[i] += trackPixel.a;
                ++total;
            }
        }
        sensorValues[i] /= total;
    }
    normalizeSensorValues();
}

void sensorMatrix::calculateSensorCenters()
{
    const float carSpriteWidth = carSprite->getTexture()->getSize().x * carSprite->getScale().x;
    const float carSpriteHeight = carSprite->getTexture()->getSize().y * carSprite->getScale().y;
    const float sensorSide = 0.075f * carSpriteWidth;
    const float padding = 0.16f * carSpriteWidth;
    const sf::Vector2f carPos = carSprite->getPosition();

    const float spriteRotationDeg = carSprite->getRotation();
    const float spriteRotationRad = 3.14159 * spriteRotationDeg / 180;

    for (int i = 0; i < 5; ++i)
    {
        const float posX = carPos.x - carSpriteWidth / 2.0f + padding + sensorSide * i * 2 + sensorSide / 2;
        const float posY = carPos.y - 3 * carSpriteHeight / 4 + sensorSide / 2;
        const float relativeX = posX - carPos.x;
        const float relativeY = posY - carPos.y;
        const float relativeDeltaX = relativeX * cos(spriteRotationRad) - relativeY * sin(spriteRotationRad);
        const float relativeDeltaY = relativeX * sin(spriteRotationRad) + relativeY * cos(spriteRotationRad);

        sensorCenters[i] = std::make_pair(carPos.x + relativeDeltaX,
                                          carPos.y + relativeDeltaY);
    }
}

void sensorMatrix::normalizeSensorValues()
{
    std::transform(begin(sensorValues),
                   end(sensorValues),
                   begin(sensorValues),
                   [] (auto x)
                   {
                        x *= 4;
                        //return  1024 - x;
                        return x;
                   });

    std::cout << "Sensor values:" << std::endl;
    std::copy(begin(sensorValues),
              end(sensorValues),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
