#ifndef OBJFILEPARSER_H
#define OBJFILEPARSER_H

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class ObjFileParser {
    public:
        ObjFileParser();
        void parseObjFile(string filename);
        vector<vector<int>> getVerticies() { return verticies; }
        vector<vector<int>> getFaces() { return faces; }

    private:
        vector<vector<int>> verticies;
        vector<vector<int>> faces;

};

#endif