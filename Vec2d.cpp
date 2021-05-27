#include "Vec2d.h"

Vec2d::Vec2d(double x, double y) {
    x = this->x;
    y = this->y;
}

Vec2d::Vec2d(vector<int> vec) {
    if (vec.size() == 2) {
        x = vec.at(0);
        y = vec.at(1);
    }
}

double Vec2d::getX() {
    return x;
}

double Vec2d::getY() {
    return y;
}