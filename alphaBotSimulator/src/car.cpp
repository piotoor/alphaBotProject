#include "car.h"

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
    sprite = new sf::Sprite;
    sprite->setTexture(*assets::getTexture("car"));
    sprite->setScale(0.2f, 0.2f);
    sprite->setOrigin(assets::getTexture("car")->getSize().x / 2.0, assets::getTexture("car")->getSize().y / 2.0);
    curveOrigin = sprite->getPosition();
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
    float left_theta  = leftAngularVelocity  * t.asMilliseconds() / 1000.0f;
    float right_theta = rightAngularVelocity * t.asMilliseconds() / 1000.0f;
    float left_l  = wheelRadius * left_theta;
    float right_l = wheelRadius * right_theta;


    using namespace std;
    cout << "left_l = " << left_l << endl;
    cout << "right_l = " << right_l << endl;
    cout << "left_theta = " << left_theta << endl;
    cout << "right_theta = " << right_theta << endl;
    cout << "pos = " << sprite->getPosition().x << " ; " << sprite->getPosition().y << endl;
    cout << "power = " << leftPower << " ; " << rightPower << endl;


    if(getDirection() == car::direction::forwards)
    {
        // change pos based on left_l and right_l
        // sprite->move(left_l, 0);
    }
    else if (getDirection() == car::direction::left)
    {






        // 1. calculate curveRadius and relative origin, based on current coords and rotation angle
        float curveRadius   = left_l * axisLength / (right_l - left_l);
        float spriteRotationRad = (360.0f - sprite->getRotation()) * pi / 180.0f;
        //sf::Vector2f O;
        float x_tmp = curveRadius * cos(spriteRotationRad);
        float y_tmp = curveRadius * sin(spriteRotationRad);
        //O.x = sprite->getPosition().x - x_tmp;
        //O.y = sprite->getPosition().y - y_tmp;
        // 2. calculate x and y in a temporary system
            // x_tmp & y_tmp ?
        // 3. calcualate current dx and dy and rotation delta
        float dalpha_rad = right_l / (curveRadius + axisLength);
        float dx = x_tmp - (x_tmp * cos(dalpha_rad) + y_tmp*sin(dalpha_rad));
        float dy = (-x_tmp * sin(dalpha_rad) + y_tmp * cos(dalpha_rad)) - y_tmp;
        // 4. apply deltas
        sprite->move(dx, dy);

        // 6. apply rotation delta
        float alpha_deg       = dalpha_rad * 180 / pi;
        sprite->rotate(-alpha_deg);


        // if curveRadius == 0, only rotate
        // else move and rotate accordingly



        cout << "dx = " << dx << endl;
        cout << "dy = " << dy << endl;


        // origin to the left
        cout << "curveRadius = " << curveRadius << endl;


        cout << "alpha_deg = " << alpha_deg << endl;
        cout << "alpha_rad = " << dalpha_rad << endl;
        cout << "sprite->rotation() = " << sprite->getRotation() << endl;


    }
    else // getDirection() == car::direction::right
    {
        float curveRadius = right_l * axisLength / (left_l - right_l);
        float alpha       = right_l / curveRadius * 180 / pi;
        // origin to the right
        cout << "curveRadius = " << curveRadius << endl;
        cout << "alpha = " << alpha << endl;
    }
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
