#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <memory>

#include "assets.h"
#include "car.h"
#include "track.h"
#include "SingleCurveGenerator.h"
#include "../alphaBotCommunicator.h"
#include <vector>

constexpr int width = 1400;
constexpr int height = 1000;

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    window.setFramerateLimit(80);

    sf::Clock clock;
    assets::loadTextures("assets");
    car c;
    track t(width, height);
    c.setTrackImage(t.getTrackImage());

    alphaBotCommunicator communicator;
	std::cout<<"Connect..."<<std::endl;
	communicator.connect();


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

        communicator.listenForGetSensorValsReq();
        std::cout<<"sendSensorValsToAlphaBot..."<<std::endl;
        int* vals = new int[5];
        std::vector<int> sensorValues = c.getSensorValues();
        copy(begin(sensorValues),
             end(sensorValues),
             vals);

        communicator.sendSensorValsToAlphaBot(vals);

        std::cout<<"sendSensorValsToAlphaBot..."<<std::endl;

        int pwma = 0;

        int pwmb = 0;


        communicator.listenForPwmUpdate(pwma, pwmb);
        std::cout << "pierwszy done" << std::endl;
        communicator.listenForPwmUpdate(pwma, pwmb);

        std::cout<<"Pwma:"<<pwma<<"Pwmb:"<<pwmb<<std::endl;

        std::cout<<"End"<<std::endl;
        c.updatePower(pwma, pwmb);


        c.update(elapsed);

        window.clear(sf::Color::White);
        window.draw(*t.getVertices());
        window.draw(*t.getVertices2());
        window.draw(*c.getSprite());
        window.display();
    }


    return 0;
}
