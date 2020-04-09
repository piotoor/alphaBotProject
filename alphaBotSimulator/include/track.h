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
        track(int width, int height, trackType type = trackType::DEFAULT, const std::vector<Point> *controlPoints = nullptr);
        virtual ~track();
        sf::VertexArray *getVertices();
        std::shared_ptr<sf::Image> getTrackImage();

    protected:
        std::unique_ptr<sf::VertexArray> vertexArray;
        std::unique_ptr<SingleCurveGenerator> scg;

    private:
        std::vector<Point>          trackPoints;
        sf::RenderTexture           trackBuffer;
        std::shared_ptr<sf::Image>  trackImage;

        int width;
        int height;


};

#endif // TRACK_H
