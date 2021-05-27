#ifndef OBJFILEPARSER_H
#define OBJFILEPARSER_H

#include <iostream>
#include <vector>
#include <string>
#include "Vec3d.h"

using std::vector;
using std::string;

class ObjFileParser {
    public:
        ObjFileParser();
        void parseObjFile(string filename);
        vector<Vec3d> getVerticies() { return verticies; }
        vector<Vec3d> getFaces() { return faces; }

    private:
        vector<Vec3d> verticies;
        vector<Vec3d> faces;

};

#endif