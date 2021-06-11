//
// This is the custom object that's derived from class Object.
// Its vertices and faces are parsed from the 3D model passed in 
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

    private:
        /** Calculate the surface normal from the cross product of 
            the two sides of the triangle
            @return The surface normal
        */
        Vec3d calcSurfNormA(Vec3d& triangle);

        /** Calculate the surface normal using Newell's Method
            @return The surface normal
        */
        Vec3d calcSurfNormB(Vec3d& triangle);
};

#endif