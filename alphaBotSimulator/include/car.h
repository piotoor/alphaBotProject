#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>

#include "assets.h"
#include "sensorMatrix.h"

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
        void                setTrackImage(std::shared_ptr<sf::Image> trackImage);


    private:
        enum class direction
        {
            forwards,
            left,
            right
        };

        car::direction getDirection();
        std::unique_ptr<sf::Sprite>  sprite;

        sensorMatrix sensors;

        float   d;    // depr
        float   dir;  // depr
        float   leftPower;
        float   rightPower;
        float   maxPower;
        float   prevLeftPower;
        float   prevRightPower;
        float   powerVelocityRatio;
        float   leftAngularVelocity;
        float   rightAngularVelocity;
        bool    forwards;
        bool    updatedPower;
        float   axisLength;
        float   wheelRadius;

        static constexpr float  pi          = 3.1415926f;
        static constexpr float  epsilon     = 0.1f;
};

#endif // CAR_H
