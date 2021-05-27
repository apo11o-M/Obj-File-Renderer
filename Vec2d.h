#ifndef VEC2D_H
#define VEC2D_H

#include <vector>

using namespace std;

class Vec2d {
    private:
        double x;
        double y;

    public:
        Vec2d(double x, double y);
        Vec2d(vector<int> vec);
        double getX();
        double getY();

};

#endif