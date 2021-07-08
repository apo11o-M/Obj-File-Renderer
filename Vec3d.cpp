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

Vec3d::Vec3d(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3d::Vec3d(vector<float> vec) {
    if (vec.size() == 3) {
        x = vec.at(0);
        y = vec.at(1);
        z = vec.at(2);
    }
}

Vec3d::Vec3d(vector<int> vec) {
    if (vec.size() == 3) {
        x = vec.at(0);
        y = vec.at(1);
        z = vec.at(2);
    }
}

float Vec3d::length() {
    return sqrt(x * x + y * y + z * z);
}

float Vec3d::distanceSquared(Vec3d& vec) {
    float xLen = vec.x - x;
    float yLen = vec.y - y;
    float zLen = vec.z - z;
    return (xLen * xLen + yLen * yLen + zLen * zLen);
}

Vec3d Vec3d::cross(Vec3d& vec) {
    Vec3d result;
    result.x = y * vec.z - z * vec.y;
    result.y = z * vec.x - x * vec.z;
    result.z = x * vec.y - y * vec.x;
    return result;
}

float Vec3d::dot(Vec3d& vec) {
    return (x * vec.x + y * vec.y + z * vec.z);
}

Vec3d Vec3d::normalize() {
    Vec3d result = Vec3d(x, y, z);
    float length = sqrt((x * x) + (y * y) + (z * z));
    return result / length;
}

Vec3d Vec3d::rotation(float rotX, float rotY, float rotZ) {
    Vec3d result;
    rotX *= M_PI / 180.0;
    rotY *= M_PI / 180.0;
    rotZ *= M_PI / 180.0;
    float sRotX = std::sin(rotX), sRotY = std::sin(rotY), sRotZ = std::sin(rotZ);
    float cRotX = std::cos(rotX), cRotY = std::cos(rotY), cRotZ = std::cos(rotZ);
    result.x = (x * cRotX * cRotY) + (y * sRotX * cRotY) - (z * sRotY);
    result.y = (x * (cRotX * sRotY * sRotZ - sRotX * cRotZ)) + (y * (sRotX * sRotY * sRotZ + cRotX * cRotZ))
                    + (z * cRotY * sRotZ);
    result.z = (x * (cRotX * sRotY * cRotZ + sRotX * sRotZ)) + (y * (sRotX * sRotY * cRotZ + cRotX * sRotZ))
                    + (z * cRotY * cRotZ);
    return result;
}

Vec2d Vec3d::projection(float k1, float k2, int width, int height) {
    Vec2d result;
    result.x = (k1 * x / (k2 + z)) + width / 2;
    result.y = (k1 * y / (k2 + z)) + height / 2;
    // The 2D coordinates in the buffer is centered in the top left corner of the window
    // since the coordinate system in sfml window has the orgin in the top left. We have
    // to offset the points in the buffer by half of the width/height of the window
    return result;
}

Vec3d Vec3d::operator+(const Vec3d& vec) {
    Vec3d result;
    result.x = this->x + vec.x;
    result.y = this->y + vec.y;
    result.z = this->z + vec.z;
    return result;
}

Vec3d Vec3d::operator-(const Vec3d& vec) {
    Vec3d result;
    result.x = this->x - vec.x;
    result.y = this->y - vec.y;
    result.z = this->z - vec.z;
    return result;
}

Vec3d Vec3d::operator*(const float val) {
    Vec3d result;
    result.x = this->x * val;
    result.y = this->y * val;
    result.z = this->z * val;
    return result;
}

Vec3d Vec3d::operator/(const float val) {
    Vec3d result;
    result.x = this->x / val;
    result.y = this->y / val;
    result.z = this->z / val;
    return result;
}

void Vec3d::operator=(const Vec3d& vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

ostream& operator<<(ostream& os, const Vec3d& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os; 
}