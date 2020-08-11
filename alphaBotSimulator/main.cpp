#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <memory>

#include "assets.h"
#include "car.h"
#include "track.h"
#include "SingleCurveGenerator.h"

constexpr int width = 1200;
constexpr int height = 800;

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    window.setFramerateLimit(80);

    sf::Clock clock;
    assets::loadTextures("assets");
    car c;
    track t(width, height);
    c.setTrackImage(t.getTrackImage());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();
        c.onKeyPressed(elapsed);
        c.update(elapsed);

//        // if(listen)
//        {
//            getSensorValues();
//        }
//        sendSensorvaluesToAlphaBot();
//        //
//        if (listenForPwmUpdate)
//         {
//             updatePwm()
//         }




        window.clear();
        window.draw(*t.getVertices());
        window.draw(*c.getSprite());
        window.display();
    }


    return 0;
}
