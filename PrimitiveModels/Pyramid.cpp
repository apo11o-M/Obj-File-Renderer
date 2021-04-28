//
// Hard coded a pyramid's five verticies and the faces that connects
// the lines

#include "Pyramid.h"

Pyramid::Pyramid() {
    verticies = {
    //   X, Y, Z coordinates
        {-100, -100, -100},     // p1
        {100, -100, -100},      // p2
        {100, 100, -100},       // p3
        {-100, 100, -100},      // p4
        {0, 0, 70}              // p5
    };
    
    faces = {
    //  p1, p2, p3
        {1, 2, 3}, {1, 3, 4},
        {1, 2, 5}, {2, 3, 5},
        {3, 4, 5}, {4, 1, 5}
    };
}



