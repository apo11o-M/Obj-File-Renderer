#include "Vec2d.h"
#include "Vec3d.h"
#include "3DModels/Faces.h"

// Utilities function for the Main.cpp
namespace util {

    // Quick sort the vectors
    void quickSort(vector<Vec3d> &arr, vector<Faces> &target, int low, int high, Vec3d &camPos);
    int partition(vector<Vec3d> &arr, vector<Faces> &target, int low, int high, Vec3d &camPos);

    // Clip the number so it's between the lower and the upper bounds
    double clip(double n, double lower, double upper);

    /** Convert the x y coordinate into the pixel array index, return -1 if the x y 
        coord is out of the current window view 
    */ 
    unsigned coordToIndex(int x, int y, int width, int height);

    // Calculate the area enclosed by the three vertices using the shoelace method
    float calcArea(Vec2d vec1, Vec2d vec2, Vec2d vec3);
}