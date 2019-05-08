#ifndef MATHHELPER_H
#define MATHHELPER_H
#include <map>
#include <vector>

using namespace std;

class SingleCurveGenerator
{
    public:
        SingleCurveGenerator(size_t numOfSegments, const vector<pair<double, double>>& controlPoints);
        ~SingleCurveGenerator();
        vector<pair<double, double>> Bezier2D();

    private:
        pair<double, double> p(double t);
        int Newton(int k);
        double Bernstein(int i, double t);

        map<pair<int, int>, int> newtonCache;
        size_t numOfSegments;
        vector<pair<double, double>> controlPoints;
        size_t order;
};

#endif // MATHHELPER_H
