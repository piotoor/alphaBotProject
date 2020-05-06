#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "assets.h"
#include "car.h"
#include "track.h"
#include "SingleCurveGenerator.h"

int width = 1200;
int height = 800;

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    window.setFramerateLimit(80);

    sf::Clock clock;
    assets::loadTextures("assets");
    car c;
    track t;

    sf::RenderTexture trackBuffer;
    trackBuffer.create(width, height);
    trackBuffer.draw(*t.getVertices());
    trackBuffer.display();
    sf::Image trackImage = trackBuffer.getTexture().copyToImage();

    c.setTrackImage(&trackImage);

//    sf::Sprite test;
//    test.setTexture(trackBuffer.getTexture());

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


        window.clear();
        window.draw(*t.getVertices());
//        window.draw(test);
        window.draw(*c.getSprite());
        window.display();
    }

    assets::disposeTextures();

    return 0;
}
