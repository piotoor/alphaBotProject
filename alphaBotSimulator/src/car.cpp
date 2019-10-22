#include "car.h"

const static float PI = 3.1415926535;

car::car()
{
    sprite = new sf::Sprite;
    sprite->setTexture(*assets::getTexture("car"));
    sprite->setOrigin(assets::getTexture("car")->getSize().x / 2.0, assets::getTexture("car")->getSize().y / 2.0);
    sprite->setScale(0.2f, 0.2f);
    d = 4.2f;
    dir = 1.0f;
}

car::~car()
{
    delete sprite;
}

void car::onKeyPressed()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sprite->rotate(-1.6f * dir);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sprite->rotate(1.6f * dir);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        dir = 1.0f;
        //sprite->move(d * sin(sprite->getRotation() * PI / 180.0), -d * cos(sprite->getRotation() * PI / 180.0));
        sprite->move(d * sin(sprite->getRotation() * PI / 180.0), -d * cos(sprite->getRotation() * PI / 180.0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        d = -d;
        dir = -1.0f;
        sprite->move(d * sin(sprite->getRotation() * PI / 180.0), -d * cos(sprite->getRotation() * PI / 180.0));
        d = -d;
    }
}

sf::Sprite *car::getSprite()
{
    return this->sprite;
}
