#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "assets.h"
#include "car.h"
int width = 1200;
int height = 800;


int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    window.setFramerateLimit(80);

    assets::loadTextures("assets");
    car c;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        c.onKeyPressed();
        window.clear();
        window.draw(*c.getSprite());
        window.display();
    }

    assets::disposeTextures();
    return 0;
}
