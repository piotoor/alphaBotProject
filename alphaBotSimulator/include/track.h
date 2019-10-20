#ifndef TRACK_H
#define TRACK_H

#include <SFML/Graphics.hpp>

#include "SingleCurveGenerator.h"
#include "assets.h"


class track
{
    public:
        enum trackType
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
        sf::VertexArray *vertexArray;
        SingleCurveGenerator *scg;

    private:
        std::vector<Point> trackPoints;


};

#endif // TRACK_H
