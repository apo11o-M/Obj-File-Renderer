#ifndef VEC3D_H
#define VEC3D_H
#include <vector>
#include <cmath>
#include <iostream>
#include <ostream>
#include "Vec2d.h"

#define M_PI 3.14159265358979323846

using std::vector;
using std::cout;
using std::endl;
using std::ostream;

class Vec3d {
    public:
        float x;
        float y;
        float z;

    public:
        // constructors
        Vec3d();
        Vec3d(const Vec3d& vec);
        Vec3d(float x, float y, float z);
        Vec3d(vector<int> vec);
        Vec3d(vector<float> vec);
        Vec3d(vector<double> vec);

        /**
            Calculate the length of the vector 
        */
        float length();

        /**
            Calculate the distance squared of the two 3d points 
        */
        float distanceSquared(Vec3d& vec);

        /**
            Calculate the cross product of the two vectors
        */
        Vec3d cross(Vec3d& vec);

        /**
            Calculate the dot product of the two vectors
        */
        float dot(Vec3d& vec);

        /**
            Normalize the vector
        */
        Vec3d normalize();

        /** 
            Do the rotation to the 3D points that's being passed in based on the dx, dy, and dz angles 
            @param vert A 3D vertex
            @param rot Amount of rotation angle on each axis
            @return The rotated 3D points
        */ 
        Vec3d rotation(float rotX, float rotY, float rotZ);

        /** 
            Do the projection that converts the passed in 3D points to the 2D points that will be 
            projected onto the screen, also consider the distance from 1). the object to the viewer, and 
            2). the object to the screen
            @param vert A 3D vertex
            @param distOS Object & screen distance
            @param distOV Object & viewer distance
            @return The projected 2D points onto the screen
        */        
        Vec2d projection(float k1, float k2, int width, int height);
    
    public:
        Vec3d operator+(const Vec3d& vec);
        Vec3d operator-(const Vec3d& vec);
        Vec3d operator*(const float val);
        Vec3d operator/(const float val);
        void operator=(const Vec3d& vec); 
        friend ostream& operator<<(ostream& os, const Vec3d& vec);

};

#endif