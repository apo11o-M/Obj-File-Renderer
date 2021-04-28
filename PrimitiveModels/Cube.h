//
// This is a Cube object that's derived from class Object. It contains 
// the verticies and the triangle that defines the model itself
//

#ifndef CUBE_H
#define CUBE_H
#include "Object.h"

class Cube : public Object {
    public:
        Cube();
        vector<vector<int>> getVert() override { return verticies; }
        vector<vector<int>> getTri() override { return faces; }

};

#endif