#ifndef CAR_H
#define CAR_H
#include <SFML/Graphics.hpp>
#include "assets.h"
#include <cmath>

class car
{
    public:
        car();
        virtual ~car();

        void onKeyPressed();
        sf::Sprite* getSprite();

    protected:
        sf::Sprite* sprite;
        float d;
        float dir;

    private:
};

#endif // CAR_H
