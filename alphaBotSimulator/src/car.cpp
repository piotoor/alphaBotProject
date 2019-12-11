#include "car.h"

const static float PI = 3.1415926535;

car::car():d(4.2f), dir(1.0f),
                    leftPower(0.0f),
                    rightPower(0.0f),
                    maxPower(100.0f),
                    powerVelocityRatio(1.0f),
                    leftAngularVelocity(0.0f),
                    rightAngularVelocity(0.0f)
{
    sprite = new sf::Sprite;
    sprite->setTexture(*assets::getTexture("car"));
    sprite->setOrigin(assets::getTexture("car")->getSize().x / 2.0, assets::getTexture("car")->getSize().y / 2.0);
    sprite->setScale(0.2f, 0.2f);
}

car::~car()
{
    delete sprite;
}

void car::onKeyPressed(sf::Time t)
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
    // power based

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
    {
        leftPower += 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
    {
        rightPower += 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
    {
        leftPower -= 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
    {
        rightPower -= 1.0f;
    }
    updatePower(leftPower, rightPower);
}

sf::Sprite *car::getSprite()
{
    return this->sprite;
}

float car::getRightPower()
{
    return leftPower;
}

float car::getLeftPower()
{
    return rightPower;
}

void car::updatePower(float leftPower, float rightPower, bool forwards)
{
    this-> leftPower  = leftPower;
    this-> rightPower = rightPower;
    this-> leftAngularVelocity  = leftPower  * powerVelocityRatio;
    this-> rightAngularVelocity = rightPower * powerVelocityRatio;
}

void car::update(sf::Time t)
{
    float left_theta  = leftAngularVelocity  * t.asMilliseconds() / 1000.0f;
    float right_theta = rightAngularVelocity * t.asMilliseconds() / 1000.0f;
    float left_l  = wheelRadius * left_theta;
    float right_l = wheelRadius * right_theta;


    using namespace std;
    cout << "left_l = " << left_l << endl;
    cout << "right_l = " << right_l << endl;
    cout << "pos = " << sprite->getPosition().x << " ; " << sprite->getPosition().y << endl;
    cout << "power = " << leftPower << " ; " << rightPower << endl;

    if(getDirection() == car::direction::forwards)
    {
        // change pos based on left_l and right_l
        sprite->move(left_l, 0);
    }
    else if (getDirection() == car::direction::left)
    {
        float curveRadius = left_l * axisLength / (right_l - left_l);
        float alpha       = -left_l / curveRadius * 180 / pi;
        // origin to the left
    }
    else // getDirection() == car::direction::right
    {
        float curveRadius = right_l * axisLength / (left_l - right_l);
        float alpha       = right_l / curveRadius * 180 / pi;
        // origin to the right
    }
}

car::direction car::getDirection()
{
    if(abs(leftPower - rightPower) < epsilon)
    {
        return car::direction::forwards;
    }
    else if(leftPower < rightPower)
    {
        return car::direction::left;
    }
    else
    {
        return car::direction::right;
    }
}
