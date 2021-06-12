// This parses the obj file in the directory into the stuff we can actually use

#include "ObjFileParser.h"
#include <stdexcept>
#include <sstream>
#include <fstream>

using std::cout;
using std::endl;
using std::getline;
using std::stringstream;

ObjFileParser::ObjFileParser() {}

void ObjFileParser::parseObjFile(string filename) {
    std::ifstream myFile;
    myFile.open(filename); 
    if (!myFile.is_open()) {
        throw std::runtime_error("The file does not exist you donkey.");
    }

    // start getline and and do stuff
    vector<double> vecSingle(3);
    vector<int> faceSingle(9);
    string line, face, vert;
    int i = 0;
    while (getline(myFile, line)) {
        i = 0;
        if (!line.empty()) {
            if (line.at(0) == 'v' && line.at(1) == ' ') {
                // this line is a vertex
                stringstream check1(line);
                while (getline(check1, vert, ' ')) {
                    if (vert != "v") {
                        vecSingle.at(i) = stod(vert) * 1.5;
                        // vecSingle.at(i) = stod(vert);
                        i++;
                    }
                }
                vertices.push_back(Vec3d(vecSingle));

            } else if (line.at(0) == 'v' && line.at(1) == 'n' && line.at(2) == ' ') { 
                // this line is a vertex normal
                stringstream check1(line);
                while (getline(check1, vert, ' ')) {
                    if (vert != "vn") {
                        vecSingle.at(i) = stod(vert);
                        i++;
                    }
                }
                vertNorm.push_back(Vec3d(vecSingle));

            } else if (line.at(0) == 'v' && line.at(1) == 't' && line.at(2) == ' ') { 
                // this line is a texture normal 
                vecSingle = {0, 0, 0};
                stringstream check1(line);
                while (getline(check1, vert, ' ')) {
                    if (vert != "vt") {
                        vecSingle.at(i) = stod(vert);
                        i++;
                    }
                }
                textNorm.push_back(Vec3d(vecSingle));  

            } else if (line.at(0) == 'f' && line.at(1) == ' ') {
                stringstream check1(line);
                while (getline(check1, face, ' ')) {
                    stringstream check2(face);
                    while (getline(check2, vert, '/') && vert != "f") {
                        if (!vert.empty()) {
                            faceSingle.at(i) = stod(vert) - 1;
                        } else {
                            faceSingle.at(i) = 0;
                        }
                        i++;
                    }
                }
                Vec3d v1(faceSingle.at(0), faceSingle.at(1), faceSingle.at(2));
                Vec3d v2(faceSingle.at(3), faceSingle.at(4), faceSingle.at(5));
                Vec3d v3(faceSingle.at(6), faceSingle.at(7), faceSingle.at(8));
                faces.push_back(Faces(v1, v2, v3));
            
            }
        }
        
    } 


}