//
// This is the base class for all of the objects that will be 
// rendered onto the screen
//

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
using std::vector;

class Object {
    public:
        // a function that can populate the verticies and 
        // triangles as the other class reads the .obj file

        // returns the verticies of the object
        vector<vector<int>> getVert() { return verticies; };
        // returns the triangles of the object
        vector<vector<int>> getTri() { return faces; };

    protected: 
        // The verticies 
        // This contains the individual verticies of the model in a three 
        // dimensional space.
        vector<vector<int>> verticies;
        
        // The triangles (faces)
        // This defines the triangle that forms when connecting the three 
        // points together.
        vector<vector<int>> faces;


};

#endif