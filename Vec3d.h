#ifndef VEC3D_H
#define VEC3D_H

#include <vector>

using namespace std;

class Vec3d {
    private:
        double x;
        double y;
        double z;

    public:
        Vec3d(double x, double y, double z);
        Vec3d(vector<int> vec);
        double getX();
        double getY();
        double getZ();

};

#endif