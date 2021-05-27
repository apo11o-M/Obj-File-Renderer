#include "Vec3d.h"

Vec3d::Vec3d(double x, double y, double z) {
    x = this->x;
    y = this->y;
    z = this->z;
}

Vec3d::Vec3d(vector<int> vec) {
    if (vec.size() == 3) {
        x = vec.at(0);
        y = vec.at(1);
        z = vec.at(2);
    }
}

double Vec3d::getX() {
    return x;
}

double Vec3d::getY() {
    return y;
}

double Vec3d::getZ() {
    return z;
}