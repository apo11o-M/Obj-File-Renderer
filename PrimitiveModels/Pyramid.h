//
// This is a Pyramid object that's derived from class Object. It contains 
// the verticies and the triangle that defines the model itself
//

#ifndef PYRAMID_H
#define PYRAMID_H
#include "Object.h"

class Pyramid : public Object {
    public:
        Pyramid();
        vector<vector<int>> getVert() override { return verticies; }
        vector<vector<int>> getTri() override { return faces; }

};

#endif