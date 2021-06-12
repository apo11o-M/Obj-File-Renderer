#ifndef OBJFILEPARSER_H
#define OBJFILEPARSER_H

#include <iostream>
#include <vector>
#include <string>
#include "Vec3d.h"
#include "3DModels/Faces.h"

using std::vector;
using std::string;

class ObjFileParser {
    public:
        ObjFileParser();
        void parseObjFile(string filename);
        vector<Vec3d> getVertices() { return vertices; }
        vector<Faces> getFaces() { return faces; }
        vector<Vec3d> getVertNorm() { return vertNorm; }
        vector<Vec3d> getTextNorm() { return textNorm; }

    private:
        vector<Vec3d> vertices;
        vector<Faces> faces;
        vector<Vec3d> vertNorm;
        vector<Vec3d> textNorm;

};

#endif