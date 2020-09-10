#include "track.h"
#include <algorithm>

track::track(int width, int height, trackType type, const std::vector<Point> *controlPoints):width(width), height(height)
{
    const int segm = 80;
    std::unique_ptr<SingleCurveGenerator> scg2;
    if(type == trackType::DEFAULT)
    {
        scg = std::make_unique<SingleCurveGenerator>(segm,
        std::vector<Point>
        {
            std::make_pair(1100.21, 0.324),
            std::make_pair(1020.23,100.11),
            std::make_pair(800.20, 300.00),
            std::make_pair(730.33, 500.22),
            std::make_pair(560.22, 573.75),
            std::make_pair(710.22, 773.75),
            std::make_pair(1020.22, 800.75),
            std::make_pair(1200.22, 900.75),

        });


        scg2 = std::make_unique<SingleCurveGenerator>(segm,
        std::vector<Point>
        {
            std::make_pair(0.21, 0.324),
            std::make_pair(100.23,200.11),
            std::make_pair(400.20, 210.00),
            std::make_pair(730.33, 260.22),
            std::make_pair(560.22, 573.75),
            std::make_pair(610.22, 473.75),
            std::make_pair(1020.22, 300.75),
            std::make_pair(1200.22, 200.75),

        });
    }
    else if (type == trackType::DEFINED)
    {
        scg = std::make_unique<SingleCurveGenerator>(segm, *controlPoints);
    }

    trackPoints = scg-> Bezier2DTriangleStrip(15.0f);
    auto trackPoints2 = scg2->Bezier2DTriangleStrip(15.0f);

    vertexArray = std::make_unique<sf::VertexArray>(sf::TriangleStrip, trackPoints.size());
    vertexArray2 = std::make_unique<sf::VertexArray>(sf::TriangleStrip, trackPoints2.size());

    for(size_t i = 0; i < trackPoints.size(); i++)
    {
        (*vertexArray)[i].position = sf::Vector2f(trackPoints[i].first, trackPoints[i].second);
        (*vertexArray)[i].color = sf::Color::Red;

        (*vertexArray2)[i].position = sf::Vector2f(trackPoints2[i].first, trackPoints2[i].second);
        (*vertexArray2)[i].color = sf::Color::Red;
    }

    trackBuffer.create(width, height);
    trackBuffer.draw(*getVertices());
    trackBuffer.draw(*(vertexArray2.get()));
    trackBuffer.display();
    trackImage = std::make_shared<sf::Image>(trackBuffer.getTexture().copyToImage());

}

track::~track()
{
}

sf::VertexArray* track::getVertices() const
{
    return vertexArray.get();
}

sf::VertexArray* track::getVertices2() const
{
    return vertexArray2.get();
}


std::shared_ptr<sf::Image> track::getTrackImage() const
{
    return trackImage;
}
