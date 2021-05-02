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

        cout << "   in ObjFileParser opening file" << endl;
    myFile.open(filename); 
    if (!myFile.is_open()) {
        throw std::runtime_error("The file does not exist you donkey.");
    }
    
    // start getline and and do stuff
    vector<int> vecSingle(3), faceSingle(3);
    string line, temp, result;
    int i = 0;
    while (getline(myFile, line)) {
        i = 0;
        if (line.at(0) == 'v' && line.at(1) == ' ') {
            stringstream sstr(line);
            while (sstr.good()) {
                getline(sstr, result, ' ');
                if (result != "v") {
                    vecSingle.at(i) = stod(result);
                    i++;
                }
            }
            verticies.push_back(vecSingle);

        } else if (line.at(0) == 'f' && line.at(1) == ' ') {
            stringstream sstr(line);
            while (sstr.good()) {
                getline(sstr, temp, ' ');
                if (temp != "f") {
                    stringstream item(temp);
                    getline(item, result, '/');
                    faceSingle.at(i) = stod(result);
                    i++;
                }
            }
            faces.push_back(faceSingle);
        }
    } 
    // cout << "   verticies" << endl;
    // for (int j = 0; j < verticies.size(); j++) {
    //     for (int k = 0; k < verticies.at(j).size(); k++) {
    //         cout << verticies.at(j).at(k) << " ";
    //     }
    //     cout << "\n";
    // }

    // cout << "   faces" << endl;
    // for (int j = 0; j < faces.size(); j++) {
    //     for (int k = 0; k < faces.at(j).size(); k++) {
    //         cout << faces.at(j).at(k) << " ";
    //     }
    //     cout << "\n";
    // }

}