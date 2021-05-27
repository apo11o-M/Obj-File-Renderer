#ifndef VEC2D_H
#define VEC2D_H

#include <vector>

using std::vector;

class Vec2d {
    public:
        double x;
        double y;

    public:
        Vec2d();
        Vec2d(const Vec2d& vec);
        Vec2d(double x, double y);
        Vec2d(vector<int> vec);


};

#endif