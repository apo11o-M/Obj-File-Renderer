//
// Hard coded a pyramid's five verticies and the faces that connects
// the lines

#include "Pyramid.h"

Pyramid::Pyramid() {
    vertices = {
    //   X, Y, Z coordinates
        Vec3d(-100, 100, -100),      // p1
        Vec3d(100, -100, -100),      // p2
        Vec3d(100, 100, -100),       // p3
        Vec3d(-100, 100, -100),      // p4
        Vec3d(0, 0, 70)              // p5
    };

    // faces = {
    // //  p1, p2, p3
    //     Vec3d(1, 2, 3), Vec3d(1, 3, 4),
    //     Vec3d(1, 2, 5), Vec3d(2, 3, 5),
    //     Vec3d(3, 4, 5), Vec3d(4, 1, 5)
    // };
}



