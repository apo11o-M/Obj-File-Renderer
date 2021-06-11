// 
// vertices will be parsed from the file
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
        vertices = parser.getVertices();
        faces = parser.getFaces();
        vertNorm = parser.getVertNorm();
        textNorm = parser.getTextNorm();
        for (int i = 0; i < faces.size(); i++) {
            Vec3d norms(faces.at(i).vert1.x, faces.at(i).vert2.x, faces.at(i).vert3.x);
            surfNorm.push_back(calcSurfNormA(norms));
        }
    } catch (std::runtime_error& e) {
        cout << e.what() << endl;
    }

}

/** There are two ways of calculating the surface normal of a triangle 
    1. The vector cross product of the two edges of the triangle, the order of the vertices
       we used in the calculation will affect the direction of the normal 
       (in or out of the surface).
    2. The sum of the vertex normal of the three vertices
*/

// calculate the surface normal by calculate the cross product of two edges of the triangle, 
// be sure to normalize the length and check the direction. 
Vec3d ObjModel::calcSurfNormA(Vec3d& vecNums) {
    Vec3d result;
    Vec3d vec1 = vertices.at(vecNums.y) - vertices.at(vecNums.x);
    Vec3d vec2 = vertices.at(vecNums.z) - vertices.at(vecNums.x);
    result = vec1.cross(vec2);
    result = result.normalize();
    return result; 
}

Vec3d ObjModel::calcSurfNormB(Vec3d& vec) {}