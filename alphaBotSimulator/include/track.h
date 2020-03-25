#ifndef TRACK_H
#define TRACK_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "SingleCurveGenerator.h"
#include "assets.h"


class track
{
    public:
        enum class trackType
        {
            DEFAULT,
            RANDOM,
            DEFINED
        };

    public:
        track(trackType type = trackType::DEFAULT, const std::vector<Point> *controlPoints = nullptr);
        virtual ~track();
        sf::VertexArray *getVertices();

    protected:
        std::unique_ptr<sf::VertexArray> vertexArray;
        std::unique_ptr<SingleCurveGenerator> scg;

    private:
        std::vector<Point> trackPoints;


};

#endif // TRACK_H
