//
// This is the base class for all of the objects that will be 
// rendered onto the screen
//

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "../Vec3d.h"
#include "../Vec2d.h"

using std::vector;

class Object {
    public:
        // a function that can populate the verticies and 
        // triangles as the other class reads the .obj file

        // returns the verticies of the object
        vector<Vec3d> getVert() { return verticies; };
        // returns the triangles of the object
        vector<Vec3d> getTri() { return faces; };

    protected: 
        // The verticies 
        // This contains the individual verticies of the model in a three 
        // dimensional space.
        vector<Vec3d> verticies;
        
        // The triangles (faces)
        // This defines the triangle that forms when connecting the three 
        // points together.
        vector<Vec3d> faces;

        // The face normals
        vector<Vec3d> normals;


};

#endif