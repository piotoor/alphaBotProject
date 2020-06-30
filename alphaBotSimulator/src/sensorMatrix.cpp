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
    float  carSpriteWidth = carSprite->getTexture()->getSize().x * carSprite->getScale().x;
    float carSpriteHeight = carSprite->getTexture()->getSize().y * carSprite->getScale().y;
    using namespace std;
    cout << "carSpriteHeight = " << carSpriteHeight << endl;
    cout << "carSpriteWidth = " << carSpriteWidth << endl;
    //sf::Vector2f carSpriteOrigin = carSprite->getOrigin();
    float sensorSide = 0.075f * carSpriteWidth;
    float padding = 0.16f * carSpriteWidth;

    sf::Vector2f carPos = carSprite->getPosition();
    std::vector<std::pair<float, float>> sensorCenters(5);

    float spriteRotationDeg = carSprite->getRotation();
    float spriteRotationRad = 3.14159 * spriteRotationDeg / 180;
    for (int i = 0; i < 5; ++i)
    {
        float posX = carPos.x - carSpriteWidth / 2.0f + padding + sensorSide * i * 2 + sensorSide / 2;
        float posY = carPos.y - 3 * carSpriteHeight / 4 + sensorSide / 2;
        float relativeX = posX - carPos.x;
        float relativeY = posY - carPos.y;
        cout << "relativeX = " << relativeX << endl;
        cout << "relativeY = " << relativeY << endl;
//        std::cout << "i -----------------------> " << i << std::endl;
//        std::cout << "posX = " << posX << std::endl;
//        std::cout << "posY = " << posY << std::endl;
//        std::cout << "relativeX = " << relativeX << std::endl;
//        std::cout << "relativeY = " << relativeY << std::endl;
        float relativeDeltaX = relativeX * cos(spriteRotationRad) - relativeY * sin(spriteRotationRad);
        float relativeDeltaY = relativeX * sin(spriteRotationRad) + relativeY * cos(spriteRotationRad);
        cout << "relativeDeltaX = " << relativeDeltaX << endl;
        cout << "relativeDeltaY = " << relativeDeltaY << endl;

        sensorCenters[i] = std::make_pair(carPos.x + relativeDeltaX,
                                          carPos.y + relativeDeltaY);
    }



//    {
//        {carPos.x - carSpriteWidth / 2 + padding + sensorSide / 2,                  carPos.y - 3 * carSpriteHeight / 2 + sensorSide / 2},
//        {carPos.x - carSpriteWidth / 2 + padding + 2 * sensorSide + sensorSide / 2, carPos.y - 3 * carSpriteHeight / 2 + sensorSide / 2},
//        {carPos.x - carSpriteWidth / 2 + padding + 4 * sensorSide + sensorSide / 2, carPos.y - 3 * carSpriteHeight / 2 + sensorSide / 2},
//        {carPos.x - carSpriteWidth / 2 + padding + 6 * sensorSide + sensorSide / 2, carPos.y - 3 * carSpriteHeight / 2 + sensorSide / 2},
//        {carPos.x - carSpriteWidth / 2 + padding + 8 * sensorSide + sensorSide / 2, carPos.y - 3 * carSpriteHeight / 2 + sensorSide / 2}
//    };

    std:: cout << "carPos.x = " << carPos.x << std::endl;
    for (const auto &x: sensorCenters) {
        std:: cout << x.first << " " << x.second << std::endl;
        //sf::Color trackPixel = trackImage->getPixel(x.first, x.second);
        //std:: cout << "(" << (int)trackPixel.r << " , " << (int)trackPixel.g << " , " << (int)trackPixel.b << ")" << std::endl;
    }

    //sf::Color trackPixel = trackImage->getPixel(sprite->getPosition().x, sprite->getPosition().y);
    //cout << "temporary sensor values: (" << (int)trackPixel.r << " , " << (int)trackPixel.g << " , " << (int)trackPixel.b << ")" << endl;

    //sprite->setOrigin(assets::getTexture("car")->getSize().x / 2.0, assets::getTexture("car")->getSize().y * 3.0 / 4.0);

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
