#define TRACE

#include <iostream>
#include "gtest/gtest.h"
#include "SingleCurveGenerator.h"
#include <sstream>

using namespace std;



TEST(SingleCurveGenerator, Bezier2DTest)
{
    const int segm = 4;
    SingleCurveGenerator scg
    (
        segm,
        {
            make_pair(110.21, 210.324),
            make_pair(10.23, 10.11),
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
    vector<Point> expectedPoints;
    ASSERT_EQ(res.size(), expectedPoints.size());
    for(size_t i = 0; i < expectedPoints.size(); i++)
    {
        ASSERT_EQ(expectedPoints[i], res[i]);
    }
}

TEST(SingleCurveGenerator, Bezier2DTriangleStrip)
{
    ASSERT_EQ(1, 0);
}
//
//TEST(SingleCurveGeneratorTest, dummyTest)
//{
//    int segm = 2;
//    SingleCurveGenerator scg(segm,
//    {
//        make_pair(110.21, 210.324),
//        make_pair(10.23, 10.11),
//        make_pair(200.2, 110.0),
//        make_pair(230.33, 320.22),
//        make_pair(430.22, 573.75),
//        make_pair(830.22, 773.75),
//        make_pair(730.22, 473.75),
//        make_pair(430.22, 173.75)
//    });
//
//    vector<pair<double, double>> resStrip = scg.Bezier2DTriangleStrip(15.0f);
//    cout << endl;
//    cout << "Bezier2D(): " << endl;
//    cout << "size = " << resStrip.size() << endl;
//    cout << "segments = " << segm << endl;
//    for(size_t i = 0; i < resStrip.size(); i++)
//    {
//        if(i % 5 == 0)
//        {
//            cout << endl;
//        }
//        cout << i << ":\t" << resStrip[i].first << "; " << resStrip[i].second << endl;
//    }
//
//    cout << endl;
//    cout << "------------------------------" << endl;
//
//    vector<pair<double, double>> res = scg.Bezier2D();
//    cout << endl;
//    cout << "Bezier2D(): " << endl;
//    cout << "size = " << res.size() << endl;
//    cout << "segments = " << segm << endl;
//    for(size_t i = 0; i < res.size(); i++)
//    {
//        if(i % 5 == 0)
//        {
//            cout << endl;
//        }
//        cout << i << ":\t" << res[i].first << "; " << res[i].second << endl;
//    }
//
//    ASSERT_EQ(1, 2);
//}
