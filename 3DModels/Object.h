//
// This is the base class for all of the objects that will be 
// rendered onto the screen
//

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "../Vec3d.h"
#include "../Vec2d.h"
#include "Faces.h"

using std::vector;

class Object {
    public:
        // a function that can populate the vertices and 
        // triangles as the other class reads the .obj file

        // returns the vertices of the object
        vector<Vec3d> getVert() { return vertices; }
        // returns the faces of the object
        vector<Faces> getTri() { return faces; }
        // returns the vertex normals of the object
        vector<Vec3d> getVertNorm() { return vertNorm; }
        // returns the face normals of the object
        vector<Vec3d> getSurfNorm() { return surfNorm; }
        // returns the face normals' position of the object
        vector<Vec3d> getSurfNormPos() { return surfNormPos; }
        // returns the texture normal of the object
        vector<Vec3d> getTextNorm() { return textNorm; }

    protected: 
        // The vertices {x, y, z}
        // This contains the individual vertices of the model in a three 
        // dimensional space.
        vector<Vec3d> vertices;
        
        // The vertex normals {x, y, z}
        vector<Vec3d> vertNorm;

        /** The triangles (faces). 
        `   Each faces have three Vec3ds, representing the vertices, 
            and each vertices contains its coords number, vertex normal number, and texture normal
            number.
        */
        vector<Faces> faces;

        // The surface normals {x, y, z}
        // calculated from the vertex normals
        vector<Vec3d> surfNorm;

        // The position of the surface normals {x, y, z}
        // calculated from the centroid of the face triangles 
        vector<Vec3d> surfNormPos;

        // The texture normals {x, y, z}
        vector<Vec3d> textNorm;

};

#endif