// 
// verticies will be parsed from the file
// 

#include "ObjModel.h"
#include <string>

using std::string;
using std::cout;
using std::endl;

ObjModel::ObjModel() {}

ObjModel::ObjModel(string filename) {
    ObjFileParser parser;
    try{
        parser.parseObjFile(filename);
            cout << "Loading Obj File.." << endl;
    } catch (std::runtime_error& e) {
        cout << e.what() << endl;
    }
    verticies = parser.getVerticies();
    faces = parser.getFaces();
}

