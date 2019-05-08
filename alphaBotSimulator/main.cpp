#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "assets.h"
#include "car.h"
#include "SingleCurveGenerator.h"
int width = 1200;
int height = 800;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    window.setFramerateLimit(80);

    assets::loadTextures("assets");
    car c;
    //SingleCurveGenerator scg(20, {make_pair(11.21, 21.324), make_pair(1.23, 0.11), make_pair(30.2, 11.0), make_pair(123.33, 232.22)});
    int segm = 3000;
    SingleCurveGenerator scg(segm,
    {
        make_pair(110.21, 210.324),
        make_pair(10.23, 10.11),
        make_pair(200.2, 110.0),
        make_pair(230.33, 320.22),
        make_pair(430.22, 573.75),
        make_pair(830.22, 773.75)
    });
    vector<pair<double, double>> res = scg.Bezier2D();
    sf::VertexArray vertices(sf::Points, res.size());

    cout << "Bezier2D(): " << endl;
    for(int i = 0; i < res.size(); i++)
    {
        cout << res[i].first << "; " << res[i].second << endl;
        vertices[i].position = sf::Vector2f(res[i].first, res[i].second);
        vertices[i].color = sf::Color::Red;
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // method handleEvents()
        c.onKeyPressed();
        window.clear();
        // method drawObjects etc
        //window.draw(*t.getSprite());
        window.draw(vertices);
        window.draw(*c.getSprite());
        window.display();
    }

    assets::disposeTextures();
    return 0;
}
