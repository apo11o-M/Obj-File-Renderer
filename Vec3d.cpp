#include "Vec3d.h"

Vec3d::Vec3d() {
    x = 0;
    y = 0;
    z = 0;
}

Vec3d::Vec3d(const Vec3d& vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

Vec3d::Vec3d(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3d::Vec3d(vector<int> vec) {
    if (vec.size() == 3) {
        x = vec.at(0);
        y = vec.at(1);
        z = vec.at(2);
    }
}
