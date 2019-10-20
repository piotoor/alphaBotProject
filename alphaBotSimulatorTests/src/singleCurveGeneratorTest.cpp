#define TRACE

#include <iostream>
#include "gtest/gtest.h"
#include "SingleCurveGenerator.h"
#include <sstream>
#include <cmath>

using namespace std;

const float epsilon = 0.001;

TEST(SingleCurveGenerator, Bezier2DTest1)
{
    const int segm = 4;
    SingleCurveGenerator scg
    (
        segm,
        {
            make_pair(110.0, 210.0),
            make_pair(10.0, 10.0),
        }
    );
    vector<Point> res = scg.Bezier2D();

#ifdef TRACE
    cout << endl;
    cout << "Bezier2D(): " << endl;
    cout << "size = " << res.size() << endl;
    cout << "segments = " << segm << endl;
    for(size_t i = 0; i < res.size(); i++)
    {
        if(i % 5 == 0)
        {
            cout << endl;
        }
        cout << i << ":\t" << res[i].first << "; " << res[i].second << endl;
    }

    cout << endl;
    cout << "------------------------------" << endl;
#endif //TRACE

    ASSERT_EQ(res.size(), segm + 1);
    vector<Point> expectedPoints
    {
        {110, 210},
        {85, 160},
        {60, 110},
        {35, 60},
        {10, 10}
    };
    ASSERT_EQ(res.size(), expectedPoints.size());
    for(size_t i = 0; i < expectedPoints.size(); i++)
    {
        ASSERT_LE(fabs(expectedPoints[i].first - res[i].first), epsilon);
        ASSERT_LE(fabs(expectedPoints[i].second - res[i].second), epsilon);
    }
}

TEST(SingleCurveGenerator, Bezier2DTest2)
{
    const int segm = 6;
    SingleCurveGenerator scg
    (
        segm,
        {
            make_pair(210.0, 192.0),
            make_pair(50.0, 90.0),
            make_pair(11.0, 12.0),
        }
    );
    vector<Point> res = scg.Bezier2D();

#ifdef TRACE
    cout << endl;
    cout << "Bezier2D(): " << endl;
    cout << "size = " << res.size() << endl;
    cout << "segments = " << segm << endl;
    for(size_t i = 0; i < res.size(); i++)
    {
        if(i % 5 == 0)
        {
            cout << endl;
        }
        cout << i << ":\t" << res[i].first << "; " << res[i].second << endl;
    }

    cout << endl;
    cout << "------------------------------" << endl;
#endif //TRACE

    ASSERT_EQ(res.size(), segm + 1);
    vector<Point> expectedPoints
    {
        {210, 192},
        {160.028, 158.667},
        {116.778, 126.667},
        {80.25, 96},
        {50.4444, 66.6667},
        {27.3611, 38.6667},
        {11, 12}
    };
    ASSERT_EQ(res.size(), expectedPoints.size());
    for(size_t i = 0; i < expectedPoints.size(); i++)
    {
        ASSERT_LE(fabs(expectedPoints[i].first - res[i].first), epsilon);
        ASSERT_LE(fabs(expectedPoints[i].second - res[i].second), epsilon);
    }
}

TEST(SingleCurveGenerator, Bezier2DTriangleStrip)
{
    int segm = 2;
    SingleCurveGenerator scg(segm,
    {
        make_pair(110.21, 210.324),
        make_pair(10.23, 10.11),
        make_pair(200.2, 110.0),
        make_pair(230.33, 320.22),
        make_pair(430.22, 573.75),
        make_pair(830.22, 773.75),
        make_pair(730.22, 473.75),
        make_pair(430.22, 173.75)
    });

    vector<pair<double, double>> res = scg.Bezier2DTriangleStrip(15.0f);
    cout << endl;
    cout << "Bezier2D(): " << endl;
    cout << "size = " << res.size() << endl;
    cout << "segments = " << segm << endl;
    for(size_t i = 0; i < res.size(); i++)
    {
        if(i % 5 == 0)
        {
            cout << endl;
        }
        cout << i << ":\t" << res[i].first << "; " << res[i].second << endl;
    }

    cout << endl;
    cout << "------------------------------" << endl;
    ASSERT_EQ(res.size(), 2 * (segm + 1));
    vector<Point> expectedPoints
    {
        {110.21, 210.324},
        {119.085, 198.231},
        {394.388, 418.897},
        {392.685, 403.994},
        {430.22, 173.75},
        {415.378, 171.581}
    };
    ASSERT_EQ(res.size(), expectedPoints.size());
    for(size_t i = 0; i < expectedPoints.size(); i++)
    {
        ASSERT_LE(fabs(expectedPoints[i].first - res[i].first), epsilon);
        ASSERT_LE(fabs(expectedPoints[i].second - res[i].second), epsilon);
    }
}
