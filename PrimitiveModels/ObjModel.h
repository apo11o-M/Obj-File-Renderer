//
// This is the custom object that's derived from class Object.
// Its verticies and faces are parsed from the 3D model passed in 
// 

#ifndef OBJMODEL_H
#define OBJMODEL_H
#include "Object.h"
#include "../ObjFileParser.h"
#include <string>

class ObjModel : public Object {
    public:
        ObjModel();
        ObjModel(std::string filename);

};

#endif