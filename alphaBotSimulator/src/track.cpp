#include "track.h"

track::track(trackType type, const std::vector<Point> *controlPoints)
{
    if(type == trackType::DEFAULT)
    {
        int segm = 80;
        scg = std::make_unique<SingleCurveGenerator>(segm,
        std::vector<Point>
        {
            std::make_pair(110.21, 210.324),
            std::make_pair(10.23, 10.11),
            std::make_pair(200.2, 110.0),
            std::make_pair(230.33, 320.22),
            std::make_pair(430.22, 573.75),
            std::make_pair(830.22, 773.75),
            std::make_pair(730.22, 473.75),
            std::make_pair(430.22, 173.75)
        });
    }
    else if (type == trackType::DEFINED)
    {
        int segm = 80;
        scg = std::make_unique<SingleCurveGenerator>(segm, *controlPoints);
    }

    trackPoints = scg-> Bezier2DTriangleStrip(15.0f);
    vertexArray = std::make_unique<sf::VertexArray>(sf::TriangleStrip, trackPoints.size());

    for(size_t i = 0; i < trackPoints.size(); i++)
    {
        (*vertexArray)[i].position = sf::Vector2f(trackPoints[i].first, trackPoints[i].second);
        (*vertexArray)[i].color = sf::Color::Red;
    }

}

track::~track()
{
}

sf::VertexArray* track::getVertices()
{
    return vertexArray.get();
}
