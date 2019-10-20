#include "SingleCurveGenerator.h"

#include <cmath>
#include <iostream>

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r)
{
    return {l.first + r.first, l.second + r.second};
}

template <typename T,typename U>
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r)
{
    return {l.first - r.first, l.second - r.second};
}

SingleCurveGenerator:: SingleCurveGenerator(size_t numOfSegments, const std::vector<Point>& controlPoints):numOfSegments(numOfSegments),
    controlPoints(controlPoints.begin(), controlPoints.end())
{

#ifdef TRACE
    std::cout << "Control points:" << std::endl;
    for(size_t i = 0; i < controlPoints.size(); i++)
    {
        std::cout << "[" << controlPoints[i].first << "; " << controlPoints[i].second << "] " << std::endl;
    }
#endif //TRACE
    this->order = controlPoints.size() - 1;
}

SingleCurveGenerator:: ~SingleCurveGenerator()
{

}

int SingleCurveGenerator:: Newton(int k)
{
    int num = 1;
    int denom = 1;

    if(newtonCache.find(std::make_pair(order, k)) == newtonCache.end())
    {
        for(unsigned int i = order - k + 1; i < order + 1; i++)
        {
            num *= i;
        }

        for(int i = 1; i < k + 1; i++)
        {
            denom *= i;
        }

        newtonCache[std::make_pair(order, k)] = num / denom;
    }

    return newtonCache[std::make_pair(order, k)];
}

double SingleCurveGenerator:: Bernstein(int i, double t)
{
    // Newton(n,i) * (t**i) * (1.0-t)**(n-i)
    return (double)Newton(i) * pow(t, (double)i) * pow(1.0 - t, (double)(order - i));
}

Point SingleCurveGenerator:: p(double t)
{
    double x = 0.0;
    double y = 0.0;

    for(unsigned int i = 0; i < controlPoints.size(); i++)
    {
        x += controlPoints[i].first * Bernstein(i, t);
        y += controlPoints[i].second * Bernstein(i, t);
    }

    return std::make_pair(x, y);
}

std::vector<Point> SingleCurveGenerator:: Bezier2D()
{
    std::vector<Point> res;
    double dt = 1.0 / (double)numOfSegments;

    for(unsigned int i = 0; i < numOfSegments + 1; i++)
    {
        res.push_back(p(i * dt));
    }

    return res;
}

std::vector<Point> SingleCurveGenerator:: Bezier2DTriangleStrip(double d)
{
    std::vector<Point> res;
    std::vector<Point> line = Bezier2D();

    for(size_t i = 0; i < line.size() ; i++)
    {
        if(i == 0)
        {
            res.push_back(line[i]);
            //Point perp = AddOffsetToVector(computePerpendicularVector(line[i + 1] - line[i], d), line[i]);
            Point perp = computePerpendicularVector(line[i + 1] - line[i], d) + line[i];
            res.push_back(perp);
        }
        else if(i == line.size() - 1)
        {
            res.push_back(line[i]);
            Point perp = computePerpendicularVector(line[i] - line[i - 1], d) + line[i];
            res.push_back(perp);
        }
        else
        {
            res.push_back(line[i]);
            Point perp = computePerpendicularVector(line[i + 1] - line[i - 1], d) + line[i];
            res.push_back(perp);
        }
    }

    return res;
}

Point SingleCurveGenerator:: computePerpendicularVector(const Point &vect, const float &distance)
{
    // vect - vector coords after moving its base to (0, 0)
    // distance - triangle strip - based line breadth
    // res - vector perpendicular to vect, anchored ad (0, 0)
    // unit - unit vector perpendicular to vect
    Point res;
    Point unit;

    res.first = vect.second;
    res.second = -vect.first;

    double len = sqrt(pow(res.first, 2.0) + pow(res.second, 2.0));

    unit.first = res.first / len;
    unit.second = res.second / len;

    res.first = unit.first * distance;
    res.second = unit.second * distance;

    return res;
    // return vector perpendicular anchored at (0, 0). Will get moved based on the middle point
}
