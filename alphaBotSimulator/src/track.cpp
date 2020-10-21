#include "track.h"
#include <algorithm>
#include <cmath>
#include <cfenv>

track::track(int width, int height, trackType type, const std::vector<Point> *controlPoints):width(width), height(height)
{
//    constexpr int width = 1400;
//    constexpr int height = 1000;

    const int segm = 500;
    std::unique_ptr<SingleCurveGenerator> scg2;
    if(type == trackType::DEFAULT)
    {
//        scg = std::make_unique<SingleCurveGenerator>(segm,
//        std::vector<Point>
//        {
////            std::make_pair(1100.21, 0.324),
////            std::make_pair(1020.23,100.11),
////            std::make_pair(800.20, 300.00),
////            std::make_pair(730.33, 500.22),
////            std::make_pair(560.22, 573.75),
////            std::make_pair(710.22, 773.75),
////            std::make_pair(1020.22, 800.75),
////            std::make_pair(1200.22, 900.75),
//            std::make_pair(0, 500),
//            std::make_pair(350, 500),
//            std::make_pair(700, 500),
//            std::make_pair(1050, 500),
//            std::make_pair(1400, 500),
//        });

        feclearexcept(FE_ALL_EXCEPT);
        const unsigned int numOfPoints = 10;
        const double dx = (double)width / numOfPoints;
        std::vector<Point> points;
        std::cout << "dx = " << dx << std::endl;
        for (double x = 0; x <= width + 2; x += dx) {
            points.push_back(std::make_pair(x, 500.0));
            std::cout << x << " ; " << points.back().second << std::endl;
        }

        //getchar();
        scg = std::make_unique<SingleCurveGenerator>(segm, points);


        scg2 = std::make_unique<SingleCurveGenerator>(segm,
        std::vector<Point>
        {
//            std::make_pair(0.21, 0.324),
//            std::make_pair(100.23,200.11),
//            std::make_pair(400.20, 210.00),
//            std::make_pair(730.33, 260.22),
//            std::make_pair(560.22, 573.75),
//            std::make_pair(610.22, 473.75),
//            std::make_pair(1020.22, 300.75),
//            std::make_pair(1200.22, 200.75),
            std::make_pair(500, 0),
            std::make_pair(600, 250),
            std::make_pair(950, 500),
            std::make_pair(975, 750),
            std::make_pair(1010, 1000),
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

    if (std::fetestexcept(FE_DIVBYZERO)) {
        std::cout << "division by zero reported\n";
    } else if (std::fetestexcept(FE_INEXACT)) {
        std::cout << "FE_INEXACT\n";
    } else if (std::fetestexcept(FE_INVALID)) {
        std::cout << "dFE_INVALID\n";
    } else if (std::fetestexcept(FE_OVERFLOW)) {
        std::cout << "dFE_OVERFLOW\n";
    } else if (std::fetestexcept(FE_UNDERFLOW)) {
        std::cout << "FE_UNDERFLOW\n";
    } else {
        std::cout << "system jest zdrowy\n";
    }

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
