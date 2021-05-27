//
// Hard coded a cube's six verticies and the faces that connects
// the lines

#include "Cube.h"

Cube::Cube() {
    verticies = {
    //   X, Y, Z coordinates
        Vec3d(-100.0, -100.0, -100.0),
        Vec3d(100.0, -100.0, -100.0),
        Vec3d(100.0, 100.0, -100.0),
        Vec3d(-100.0, 100.0, -100.0),
        Vec3d(-100.0, -100.0, 100.0),
        Vec3d(100.0, -100.0, 100.0),
        Vec3d(100.0, 100.0, 100.0),
        Vec3d(-100.0, 100.0, 100.0)
    };
    
    faces = {
    //  p1, p2, p3
        Vec3d(1, 2, 4), Vec3d(2, 3, 4),
        Vec3d(1, 2, 6), Vec3d(1, 5, 6),
        Vec3d(4, 1, 5), Vec3d(4, 8, 5),
        Vec3d(3, 4, 8), Vec3d(3, 7, 8),
        Vec3d(2, 3, 7), Vec3d(2, 6, 7),
        Vec3d(5, 6, 8), Vec3d(6, 7, 8)
        // {0, 1, 3}, {1, 2, 3},
        // {0, 1, 5}, {0, 4, 5},
        // {3, 0, 4}, {3, 7, 4},
        // {2, 3, 7}, {2, 6, 7},
        // {1, 2, 6}, {1, 5, 6},
        // {4, 5, 7}, {5, 6, 7}
    };
}
