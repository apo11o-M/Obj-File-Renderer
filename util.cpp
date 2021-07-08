#include "util.h"

namespace util {

    // Quick sort the vectors
    void quickSort(vector<Vec3d> &arr, vector<Faces> &target, int low, int high, Vec3d &camPos) {
        if (low < high) {
            int pi = partition(arr, target, low, high, camPos);
            quickSort(arr, target, low, pi - 1, camPos);
            quickSort(arr, target, pi + 1, high, camPos);
        }
    }

    int partition(vector<Vec3d> &arr, vector<Faces> &target, int low, int high, Vec3d &camPos) {
        double pivot = arr.at(high).distanceSquared(camPos);
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr.at(j).distanceSquared(camPos) <= pivot) {
                i++;
                //swap arr[i] and arr[j]
                Vec3d temp = arr.at(j);
                arr.at(j) = arr.at(i);
                arr.at(i) = temp;
                Faces temp2 = target.at(j);
                target.at(j) = target.at(i);
                target.at(i) = temp2;
            }
        }
        // swap arr[i + 1], arr[high]
        Vec3d temp = arr.at(high);
        arr.at(high) = arr.at(i + 1);
        arr.at(i + 1) = temp;
        Faces temp2 = target.at(high);
        target.at(high) = target.at(i + 1);
        target.at(i + 1) = temp2;

        return (i + 1);
    }

    // Clip the number so it's between the lower and the upper bounds
    double clip(double n, double lower, double upper) {
        return std::max(lower, std::min(n, upper));
    }

    // Convert the x y coordinate into the pixel array index, return -1 if the x y coord is out of the 
    // current window view
    unsigned coordToIndex(int x, int y, int width, int height) {
        unsigned index;
        if ((width * height - 1) < (y * width + x) || x < 0 || y < 0) {
            // cout << "x: " << x << " y: " << y;
            // cout << ", out of bounds" << endl;
            return -1;
        } else {
            index = 4 * (x + y * width);
            return index;
        }
    }

    // Calculate the area enclosed by the three vertices using the shoelace method
    float calcArea(Vec2d vec1, Vec2d vec2, Vec2d vec3) {
        float result = 0.5 * ((vec1.x * vec2.y + vec2.x * vec3.y + vec3.x * vec1.y)
                            - (vec1.y * vec2.x + vec2.y * vec3.x + vec3.y * vec1.x));
        return result;
    }
}