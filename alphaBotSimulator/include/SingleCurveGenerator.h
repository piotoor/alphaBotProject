#ifndef MATHHELPER_H
#define MATHHELPER_H
#include <map>
#include <vector>

using namespace std;

using Point = pair<double, double>;



template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r);
template <typename T,typename U>
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r);

class SingleCurveGenerator
{
    public:
        SingleCurveGenerator(size_t numOfSegments, const vector<Point>& controlPoints);
        ~SingleCurveGenerator();
        vector<Point> Bezier2D();
        vector<Point> Bezier2DTriangleStrip(double d);

    private:
        Point p(double t);
        int Newton(int k);
        double Bernstein(int i, double t);

        map<pair<int, int>, int> newtonCache;
        size_t numOfSegments;
        vector<Point> controlPoints;
        size_t order;

        Point computePerpendicularVector(const Point &vect, const float &distance);
        Point AddOffsetToVector(Point vect, const Point &offset);
};

#endif // MATHHELPER_H
