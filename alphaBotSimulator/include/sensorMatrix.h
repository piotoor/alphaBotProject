#ifndef SENSORMATRIX_H
#define SENSORMATRIX_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

class sensorMatrix
{
    public:
        sensorMatrix();
        virtual ~sensorMatrix();

        std::vector<int>    getSensorValues() const;
        void                setTrackImage(std::shared_ptr<sf::Image> trackImage);
        void                setCarSprite(std::shared_ptr<sf::Sprite> carSprite);
        void                calculateSensorValues();

    private:
        std::vector<int>                sensorValues = {0, 0, 0, 0, 0};
        std::shared_ptr<sf::Image>      trackImage;
        std::shared_ptr<sf::Sprite>     carSprite;
};

#endif // SENSORMATRIX_H
