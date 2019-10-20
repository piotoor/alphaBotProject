#ifndef TRACK_H
#define TRACK_H
#include "SingleCurveGenerator.h"
#include <SFML/Graphics.hpp>
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
        track(trackType type = trackType::DEFAULT, const vector<Point> *controlPoints = nullptr);
        virtual ~track();
        sf::VertexArray *getVertices();

    protected:
        sf::VertexArray *vertexArray;
        SingleCurveGenerator *scg;

    private:
        vector<Point> trackPoints;


};

#endif // TRACK_H
