#include "car.h"
#include <climits>

const static float PI = 3.1415926535;

car::car():d(4.2f), dir(1.0f),
                    leftPower(0.0f),
                    rightPower(0.0f),
                    maxPower(100.0f),
                    prevLeftPower(0.0f),
                    prevRightPower(0.0f),
                    powerVelocityRatio(0.1f),
                    leftAngularVelocity(0.0f),
                    rightAngularVelocity(0.0f),
                    updatedPower(false)
{
    //sprite = new sf::Sprite;
    sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(*assets::getTexture("car"));
    sprite->setScale(0.2f, 0.2f);
    sprite->setOrigin(assets::getTexture("car")->getSize().x / 2.0, assets::getTexture("car")->getSize().y * 3.0 / 4.0);
    sprite->setPosition(800.0f, 800.0f);
    axisLength = sprite->getTexture()->getSize().x * sprite->getScale().x;
    wheelRadius = 92 * sprite->getScale().y;
    sensors.setCarSprite(sprite);
}

car::~car()
{

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
        sprite->move(d * sin(sprite->getRotation() * PI / 180.0), -d * cos(sprite->getRotation() * PI / 180.0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        dir = -1.0f;
        sprite->move(-d * sin(sprite->getRotation() * PI / 180.0), d * cos(sprite->getRotation() * PI / 180.0));
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        sprite->setOrigin(sprite->getOrigin() * 1.01f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        sprite->setOrigin(sprite->getOrigin() * 0.99f);
    }

    updatePower(leftPower, rightPower);
}

sf::Sprite *car::getSprite()
{
    return this->sprite.get();
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
    updatedPower = false;

    this-> leftPower  = leftPower;
    this-> rightPower = rightPower;
    this-> leftAngularVelocity  = leftPower  * powerVelocityRatio;
    this-> rightAngularVelocity = rightPower * powerVelocityRatio;

    if(leftPower != prevLeftPower || rightPower != prevRightPower)
    {
        updatedPower = true;
    }

    prevLeftPower = leftPower;
    prevRightPower = rightPower;
}

void car::update(sf::Time t)
{
    float leftTheta  = leftAngularVelocity  * t.asMilliseconds() / 1000.0f;
    float rightTheta = rightAngularVelocity * t.asMilliseconds() / 1000.0f;
    float leftDistance  = wheelRadius * leftTheta;
    float rightDistance = wheelRadius * rightTheta;


    using namespace std;
    cout << "left_l = " << leftDistance << endl;
    cout << "right_l = " << rightDistance << endl;
    cout << "left_theta = " << leftTheta << endl;
    cout << "right_theta = " << rightTheta << endl;
    cout << "pos = " << sprite->getPosition().x << " ; " << sprite->getPosition().y << endl;
    cout << "power = " << leftPower << " ; " << rightPower << endl;


    // 1. calculate curveRadius and relative origin, based on current coords and rotation angle
    float curveRadius = std::numeric_limits<float>::max();
    float spriteRotationRad = 0.0f;
    float rotatingTempSystemOriginX = 0.0f;


    if(getDirection() == car::direction::left)
    {
        curveRadius   = max(axisLength / 2, abs(leftDistance * axisLength / (rightDistance - leftDistance)));
        spriteRotationRad = (360.0f - sprite->getRotation()) * pi / 180.0f;
        rotatingTempSystemOriginX = curveRadius * cos(spriteRotationRad);
    }
    else if(getDirection() == car::direction::right)
    {
        curveRadius   = max(axisLength / 2, abs(rightDistance * axisLength / (leftDistance - rightDistance)));
        spriteRotationRad = -(360.0f - sprite->getRotation()) * pi / 180.0f;
        rotatingTempSystemOriginX = -curveRadius * cos(spriteRotationRad);
    }

    float rotatingTempSystemOriginY = curveRadius * sin(spriteRotationRad);
    cout << "x_tmp = " << rotatingTempSystemOriginX << endl;
    cout << "y_tmp = " << rotatingTempSystemOriginY << endl;

    // 2. calcualate current dx and dy and rotation delta
    float dalpha_rad = 0.0f;
    if(getDirection() == car::direction::left)
    {
        dalpha_rad = rightDistance / (curveRadius + axisLength);
    }
    else if(getDirection() == car::direction::right)
    {
        dalpha_rad = -leftDistance / (curveRadius + axisLength);
    }

    float dx = 0.0f;
    float dy = 0.0f;

    if(getDirection() == car::direction::left || getDirection() == car::direction::right)
    {
        dx =  rotatingTempSystemOriginX - (rotatingTempSystemOriginX * cos(dalpha_rad) + rotatingTempSystemOriginY*sin(dalpha_rad));
        dy = (-rotatingTempSystemOriginX * sin(dalpha_rad) + rotatingTempSystemOriginY * cos(dalpha_rad)) - rotatingTempSystemOriginY;
    }
    else
    {
        dx = leftDistance * sin(sprite->getRotation() * PI / 180.0);
        dy = -leftDistance * cos(sprite->getRotation() * PI / 180.0);
    }
    // 3. apply deltas
    sprite->move(dx, dy);

    // 4. apply rotation delta
    float alpha_deg = 0.0f;
    if(getDirection() == car::direction::left)
    {
        alpha_deg = dalpha_rad * 180 / pi;
    }
    else if(getDirection() == car::direction::right)
    {
        alpha_deg = dalpha_rad * 180 / pi;
    }

    sprite->rotate(-alpha_deg);

    cout << "dx = " << dx << endl;
    cout << "dy = " << dy << endl;
    cout << "curveRadius = " << curveRadius << endl;
    cout << "alpha_deg = " << alpha_deg << endl;
    cout << "alpha_rad = " << dalpha_rad << endl;
    cout << "sprite->rotation() = " << sprite->getRotation() << endl;
    cout << "Sensor values: " << endl;
    sensors.calculateSensorValues();
    sensors.getSensorValues();
    cout << endl;
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

void car::setTrackImage(std::shared_ptr<sf::Image> trackImage)
{
    this->sensors.setTrackImage(trackImage);
}

std::vector<int> car::getSensorValues() {
    return sensors.getSensorValues();
}
