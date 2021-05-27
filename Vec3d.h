#ifndef VEC3D_H
#define VEC3D_H

#include <vector>

using std::vector;

class Vec3d {
    public:
        double x;
        double y;
        double z;

    public:
        Vec3d();
        Vec3d(const Vec3d& vec);
        Vec3d(double x, double y, double z);
        Vec3d(vector<int> vec);


};

#endif