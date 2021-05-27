#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Fps.cpp"
#include "PrimitiveModels/Pyramid.h"
#include "PrimitiveModels/Cube.h"
#include "PrimitiveModels/ObjModel.h"
#include "ObjFileParser.h"
#include "Vec2d.h"
#include "Vec3d.h"


#define M_PI 3.14159265358979323846

using std::vector;
using std::cout;
using std::endl;
using sf::Vector2f;

/** 
    Do the rotation to the 3D points that's being passed in based on the dx, dy, and dz angles 
    @param vert A 3D vertex
    @param rot Amount of rotation angle on each axis
    @return The rotated 3D points
*/ 
Vec3d rotation(Vec3d vert, double rotX, double rotY, double rotZ);

/** 
    Do the projection that converts the passed in 3D points to the 2D points that will be 
    projected onto the screen, also consider the distance from 1). the object to the viewer, and 
    2). the object to the screen
    @param vert A 3D vertex
    @param distOS Object & screen distance
    @param distOV Object & viewer distance
    @return The projected 2D points onto the screen
*/
Vec2d projection(Vec3d vert, double k1, double k2, int width, int height);


int main() {
    cout << "\nProgram Start.." << endl;

    // The width and height of the window
    const int width = 1000, height = 700;
    // The rotation rate at each axis in degrees, default is 0
    double rotX = 0, rotY = 0, rotZ = 0;
    // The distance between the object and the viewer
    double k2 = 800.0;    
    // The distance between the object and the screen
    double k1 = 700.0;    
    // the framerate/update rate
    int framerate = 144;
    // whether or not pause the game
    bool pause = false;
    bool right = false, left = false, up = false, down = false;

    sf::RenderWindow window(sf::VideoMode(width, height), "yo the window is showing stuff");
    window.setFramerateLimit(framerate);
    FPS fps;
    

    ObjModel block("ObjModelFiles/utah_teapot_noslash.obj");
    // ObjModel block("ObjModelFiles/utah_teapot.obj");
    // ObjModel block("cone.obj");
    // Cube block;
    // Pyramid block;

    // Get the verticies and the triangles from the cube
    
    // The model's original verticies, should not be changed 
    const vector<Vec3d> modelVert = block.getVert();
    // The model's original triangles, should not be changed
    const vector<Vec3d> modelTri = block.getTri();
    // The buffer verticies for the block, represents the actual coord of the model in the 3d space 
    vector<Vec3d> blockVert = block.getVert(); 
    // The buffer triangles for the block, represents the actual coord of the model in the 3d space 
    vector<Vec3d> blockTri = block.getTri();
    // The buffer coordinates of the model on a 2D screen.
    vector<Vec2d> screenVert(blockVert.size(), Vec2d());
    
    cout << "Block Verticies: " << endl;
    for (int i = 0; i < blockVert.size(); i++) {
        for (int j = 0; j < 3; j++) {
            cout << blockVert.at(i).x << " "
                 << blockVert.at(i).y << " "
                 << blockVert.at(i).z << " " << endl;
        }
        cout << endl;
    }

    // The buff vertex array stores all the lines that we will be drawing, the reason 
    // why we multiply by six is because we need 6 points to draw 3 lines
    // sf::VertexArray* buff = new sf::VertexArray(sf::Lines, blockTri.size() * 6);
    sf::VertexArray buff(sf::Lines, blockTri.size() * 6);
        cout << "   buff vertex count " << buff.getVertexCount() << endl;

    // start the game loop
    while (window.isOpen()) {
        // Event handlers
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::Closed):
                    // check to close the window
                    window.close();
                    break;
                case (sf::Event::KeyPressed):
                    // check if keys are pressed
                    if (event.key.code == sf::Keyboard::Space) { pause = !pause; }
                    else if (event.key.code == sf::Keyboard::Up) {up = true;}
                    else if (event.key.code == sf::Keyboard::Down) {down = true;}
                    else if (event.key.code == sf::Keyboard::Left) {left = true;}
                    else if (event.key.code == sf::Keyboard::Right) {right = true;}
                    break;
                default:
                    break;
            }
        }

        // update the window's title to the current frame per second
        fps.update();
        window.setTitle("yo the window is showing stuff, Fps: " + std::to_string(fps.getFPS()));

        // calculate the rotation and the projection of the 3D verticies, and store
        // the 2D points in the screenVert vector
        for (int i = 0; i < blockVert.size(); i++) {
            Vec3d temp = rotation(blockVert.at(i), rotX, rotY, rotZ);
            screenVert.at(i) = projection(temp, k1, k2, width, height);
            // cout << "Coord: " << screenVert.at(i).at(0) << ", " << screenVert.at(i).at(1) << endl;
                        // floating point errors?
                        // blockVert.at(i) = rotation(blockVert.at(i), rotX, rotY, rotZ);
                        // screenVert.at(i) = projection(blockVert.at(i), k1, k2, width, height);
        }

        // store the 2D verticies that we calculated from the previous rotation and projection calculation 
        // into the buffer so the SFML knows what to draw. Use the blockTri that shows the vertices that 
        // forms the triangles, we would need a total of 3 lines, or 6 points for each arragements 
        // (point 1-2, 2-3, 3-1). And yes the order of which we insert the vertex object matters since the 
        // buffer uses those points to connect the lines
        for (int i = 0; i < blockTri.size(); i++) {
            // Calculated 2D vert, faces, face #, the vert # in the face, (0 = x, 1 = y)  
            buff[0 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).x - 1).x,
                                                (float)screenVert.at(blockTri.at(i).x - 1).y);
            buff[1 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).y - 1).x,
                                                (float)screenVert.at(blockTri.at(i).y - 1).y);

            buff[2 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).y - 1).x,
                                                (float)screenVert.at(blockTri.at(i).y - 1).y);
            buff[3 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).z - 1).x,
                                                (float)screenVert.at(blockTri.at(i).z - 1).y);

            buff[4 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).z - 1).x,
                                                (float)screenVert.at(blockTri.at(i).z - 1).y);
            buff[5 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).y - 1).x,
                                                (float)screenVert.at(blockTri.at(i).y - 1).y);                                           
        }

        // clear the window with black background
        window.clear(sf::Color::Black);

        // draw & display stuff
        window.draw(buff);
        window.display();

        // Update the rotation angle
        if (!pause) {
            rotX += 0.1;
            rotY += 0.3;
            // rotZ += 0.3;
        } else if (up) {
            rotX += 1;
            up = false;
        } else if (down) {
            rotX -= 1;
            down = false;
        } else if (left) {
            rotY -= 1;
            left = false;
        } else if (right) {
            rotY += 1;
            right = false;
        }
    }

    buff.clear();
    cout << "..Finished\n" << endl;
    return 0;
}

Vec3d rotation(Vec3d vert, double rotX, double rotY, double rotZ) {
    Vec3d result;
    int x = vert.x, y = vert.y, z = vert.z;
    rotX *= M_PI / 180.0;
    rotY *= M_PI / 180.0;
    rotZ *= M_PI / 180.0;
    double sRotX = std::sin(rotX), sRotY = std::sin(rotY), sRotZ = std::sin(rotZ);
    double cRotX = std::cos(rotX), cRotY = std::cos(rotY), cRotZ = std::cos(rotZ);

    result.x = (x * cRotX * cRotY) + (y * sRotX * cRotY) - (z * sRotY);
    result.y = (x * (cRotX * sRotY * sRotZ - sRotX * cRotZ)) + (y * (sRotX * sRotY * sRotZ + cRotX * cRotZ))
                    + (z * cRotY * sRotZ);
    result.z = (x * (cRotX * sRotY * cRotZ + sRotX * sRotZ)) + (y * (sRotX * sRotY * cRotZ + cRotX * sRotZ))
                    + (z * cRotY * cRotZ);
    return result;
}

Vec2d projection(Vec3d vert, double k1, double k2, int width, int height) {
    Vec2d result;
    int x = vert.x, y = vert.y, z = vert.z;

    result.x = (k1 * x / (k2 + z)) + width / 2;
    result.y = (k1 * y / (k2 + z)) + height / 2;

    // The 2D coordinates in the buffer is centered in the top left corner of the window
    // since the coordinate system in sfml window has the orgin in the top left. We have
    // to offset the points in the buffer by half of the width/height of the window
    return result;
}

