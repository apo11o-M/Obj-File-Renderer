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
        
        // Calculate the surface normals from the cross product of the vertices
        for (unsigned i = 0; i < faces.size(); i++) {
            Vec3d verts(faces.at(i).vert1.x, faces.at(i).vert2.x, faces.at(i).vert3.x);
            surfNorm.push_back(calcSurfNormA(verts));
        }

        // Calculate the position of the surface normals from the vertices
        for (unsigned i = 0; i < faces.size(); i++) {
            Vec3d vert1(vertices.at(faces.at(i).vert1.x));
            Vec3d vert2(vertices.at(faces.at(i).vert2.x));
            Vec3d vert3(vertices.at(faces.at(i).vert3.x));
            Vec3d centroid = (vert1 + vert2 + vert3) / 3;
            surfNormPos.push_back(centroid);
        }

    } catch (std::runtime_error& e) {
        cout << e.what() << endl;
    }
}

/** There are two ways of smoothing the edges*
    One is to do it 100%, merge every vertex normal at this vertex into one single normal. This is 
    relatively simple and the number of unique vertex normals will be limited to the number of 
    vertex this model. It is also pretty simple to implement.
    The other is don't do it 100%, but a given variable amount of "merge". This could create a 
    realistic look between harsh and shallow angles, ut the number of unique vertex may skyrocket
    when the model has lots of faces, which result in a large number different normals at each
    vertices. The amount of work to achieve this affect so is also really mind boggling. 
*/
ObjModel::ObjModel(string filename, float angle) : ObjModel(filename) {
    vector<Vec3d> norm;
    norm.resize(vertices.size());
    vector<vector<int>> normList;
    normList.resize(vertices.size());
    
    for (int i = 0; i < faces.size(); i++) {
        normList.at(faces.at(i).vert1.x).push_back(faces.at(i).vert1.z);
        normList.at(faces.at(i).vert2.x).push_back(faces.at(i).vert2.z);
        normList.at(faces.at(i).vert3.x).push_back(faces.at(i).vert3.z);
        faces.at(i).vert1.z = faces.at(i).vert1.x;
        faces.at(i).vert2.z = faces.at(i).vert2.x;
        faces.at(i).vert3.z = faces.at(i).vert3.x;
    }

    for (unsigned i = 0; i < normList.size(); i++) {
        Vec3d result;
        for (unsigned j = 0; j < normList.at(i).size(); j++) {
            result = result + vertNorm.at(normList.at(i).at(j));
        }
        result = result.normalize();
        norm.at(i) = result;
    }
    vertNorm.clear();
    vertNorm = norm;
}

/** There are two ways of calculating the surface normal of a triangle 
    1. The vector cross product of the two edges of the triangle, the order of the vertices
       we used in the calculation will affect the direction of the normal 
       (in or out of the surface).
    2. The sum of the vertex normal of the three vertices
        *** okay somehow this doesn't work, no idea why ¯\_(ツ)_/¯ ***
        Maybe I'll come back some time in the future (I'm too lazy rn lol)
*/

// Calculate the surface normal by calculate the cross product of two edges of the triangle, 
// be sure to normalize the length and check the direction. 
Vec3d ObjModel::calcSurfNormA(Vec3d& vecNums) {
    Vec3d result;
    Vec3d vec1 = vertices.at(vecNums.y) - vertices.at(vecNums.x);
    Vec3d vec2 = vertices.at(vecNums.z) - vertices.at(vecNums.x);
    result = vec1.cross(vec2);
    result = result.normalize();
    return result; 
}

// // Calculate the surface normal by suming up all the vertex normals
// Vec3d ObjModel::calcSurfNormB(Vec3d& vecNums) {
//     Vec3d result;
//     result = vertNorm.at(vecNums.x) + vertNorm.at(vecNums.y) + vertNorm.at(vecNums.z);
//     result = result.normalize();
//     return result;
// }