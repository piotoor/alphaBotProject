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


std::vector<int>& sensorMatrix::getSensorValues()
{
    const float  carSpriteWidth = carSprite->getTexture()->getSize().x * carSprite->getScale().x;
    const float carSpriteHeight = carSprite->getTexture()->getSize().y * carSprite->getScale().y;

    const float sensorSide = 0.075f * carSpriteWidth;
    const float padding = 0.16f * carSpriteWidth;

    const sf::Vector2f carPos = carSprite->getPosition();
    std::vector<std::pair<float, float>> sensorCenters(5);

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

    for (const auto &x: sensorCenters) {
        std:: cout << x.first << " " << x.second << std::endl;
    }

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

