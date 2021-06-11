#ifndef FACES_H
#define FACES_H

#include "../Vec3d.h"
#include <vector>

/** Contains the three vertices in the triangle, vert1, vert2, and vert3. 
    vert.x = vertex number, vert.y = texture norm number, vert.z = vertex norm number 
 */
class Faces {
    public:
        // x = vertex number, y = texture norm number, z = vertex norm number 
        Vec3d vert1;
        // x = vertex number, y = texture norm number, z = vertex norm number
        Vec3d vert2;
        // x = vertex number, y = texture norm number, z = vertex norm number
        Vec3d vert3;

    public:
        Faces() {};
        Faces(const Vec3d& vec1, const Vec3d& vec2, const Vec3d& vec3) {
            vert1 = vec1;
            vert2 = vec2;
            vert3 = vec3;
        }

};

#endif