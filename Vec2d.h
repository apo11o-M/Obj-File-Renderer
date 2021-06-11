#ifndef VEC2D_H
#define VEC2D_H

#include <vector>
#include <ostream>

using std::ostream;
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

    public:
        Vec2d operator+(const Vec2d& vec);
        Vec2d operator-(const Vec2d& vec);
        Vec2d operator*(const double val);
        Vec2d operator/(const double val);
        void operator=(const Vec2d& vec); 
        friend ostream& operator<<(ostream& os, const Vec2d& vec);

};

#endif