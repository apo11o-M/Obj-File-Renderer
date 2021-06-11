#include "Vec2d.h"

Vec2d::Vec2d() {
    x = 0;
    y = 0;
}

Vec2d::Vec2d(const Vec2d& vec) {
    x = vec.x;
    y = vec.y;
}

Vec2d::Vec2d(double inputX, double inputY) {
    this->x = inputX;
    this->y = inputY;
}

Vec2d::Vec2d(vector<int> vec) {
    if (vec.size() == 2) {
        x = vec.at(0);
        y = vec.at(1);
    }
}

Vec2d Vec2d::operator+(const Vec2d& vec) {
    Vec2d result;
    result.x = this->x + vec.x;
    result.y = this->y + vec.y;
    return result;
}

Vec2d Vec2d::operator-(const Vec2d& vec) {
    Vec2d result;
    result.x = this->x - vec.x;
    result.y = this->y - vec.y;
    return result;
}

Vec2d Vec2d::operator*(const double val) {
    Vec2d result;
    result.x = this->x * val;
    result.y = this->y * val;
    return result;
}

Vec2d Vec2d::operator/(const double val) {
    Vec2d result;
    result.x = this->x / val;
    result.y = this->y / val;
    return result;
}

void Vec2d::operator=(const Vec2d& vec) {
    x = vec.x;
    y = vec.y;
}
ostream& operator<<(ostream& os, const Vec2d& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os; 
}
