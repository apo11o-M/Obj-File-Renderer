#include "Vec2d.h"

Vec2d::Vec2d() {
    x = 0;
    y = 0;
}

Vec2d::Vec2d(const Vec2d& vec) {
    x = vec.x;
    y = vec.y;
}

Vec2d::Vec2d(double x, double y) {
    this->y = y;
    this->x = x;
}

Vec2d::Vec2d(vector<int> vec) {
    if (vec.size() == 2) {
        x = vec.at(0);
        y = vec.at(1);
    }
}
