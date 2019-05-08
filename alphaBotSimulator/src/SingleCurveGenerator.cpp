#include "SingleCurveGenerator.h"
#include <cmath>
#include <iostream>
using namespace std;

SingleCurveGenerator:: SingleCurveGenerator(size_t numOfSegments, const vector<pair<double, double>>& controlPoints):numOfSegments(numOfSegments),
    controlPoints(controlPoints.begin(), controlPoints.end())
{
    for(int i = 0; i < controlPoints.size(); i++)
    {
        cout << "[" << controlPoints[i].first << "; " << controlPoints[i].second << "] ";
    }
    cout << endl;
    this->order = controlPoints.size() - 1;
}

SingleCurveGenerator:: ~SingleCurveGenerator()
{

}

int SingleCurveGenerator:: Newton(int k)
{
    int num = 1;
    int denom = 1;
    if(newtonCache.find(make_pair(order, k)) == newtonCache.end())
    {
        for(unsigned int i = order - k + 1; i < order + 1; i++)
        {
            num *= i;
        }
        for(int i = 1; i < k + 1; i++)
        {
            denom *= i;
        }
        newtonCache[make_pair(order, k)] = num / denom;
    }

    return newtonCache[make_pair(order, k)];
}

double SingleCurveGenerator:: Bernstein(int i, double t)
{
    // Newton(n,i) * (t**i) * (1.0-t)**(n-i)
    //cout << Newton(i) << endl;
    return (double)Newton(i) * pow(t, (double)i) * pow(1.0 - t, (double)(order - i));
}

//vector<pair<double, double>> controlPoints;
pair<double, double> SingleCurveGenerator:: p(double t)
{
    double x = 0.0;
    double y = 0.0;
    for(unsigned int i = 0; i < controlPoints.size(); i++)
    {
        x += controlPoints[i].first * Bernstein(i, t);

        cout << "i = " << i << "; t = " << t << "; " << Bernstein(i, t) << endl;
        y += controlPoints[i].second * Bernstein(i, t);
    }
    return make_pair(x, y);
}

vector<pair<double, double>> SingleCurveGenerator:: Bezier2D()
{
    vector<pair<double, double>> res;
    double dt = 1.0 / (double)numOfSegments;
    for(unsigned int i = 0; i < numOfSegments + 1; i++)
    {
        res.push_back(p(i * dt));
    }
    return res;
}

