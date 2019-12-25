#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "assets.h"

class car
{
    public:
        car();
        virtual ~car();

        void                onKeyPressed(sf::Time t); //depr
        sf::Sprite*         getSprite();
        void                updatePower(float leftPower, float rightPower, bool forwards = true);
        float               getLeftPower();
        float               getRightPower();
        std::vector<int>    getSensorValues();
        void                update(sf::Time t);


    private:
        enum class direction
        {
            forwards,
            left,
            right
        };

        car::direction getDirection();

        sf::Sprite          *sprite;
        sf::Vector2<float>   v; // depr ?

        float   d;    // depr
        float   dir;  // depr
        float   leftPower;
        float   rightPower;
        float   maxPower;
        float   powerVelocityRatio;
        float   leftAngularVelocity;
        float   rightAngularVelocity;
        bool    forwards;

        static constexpr float  wheelRadius = 10.0f;
        static constexpr float  axisLength  = 100.0f;
        static constexpr float  pi          = 3.1415926f;
        static constexpr float  epsilon     = 0.1f;
};

#endif // CAR_H
