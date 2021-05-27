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
vector<int> rotation(vector<int> vert, double rotX, double rotY, double rotZ);

/** 
    Do the projection that converts the passed in 3D points to the 2D points that will be 
    projected onto the screen, also consider the distance from 1). the object to the viewer, and 
    2). the object to the screen
    @param vert A 3D vertex
    @param distOS Object & screen distance
    @param distOV Object & viewer distance
    @return The projected 2D points onto the screen
*/
vector<int> projection(vector<int> vert, double k1, double k2, int width, int height);


int main() {
    cout << "\nProgram Start.." << endl;

    // The width and height of the window
    const int width = 1000, height = 700;
    // The rotation rate at each axis in degrees, default is 0
    double rotX = 0, rotY = 0, rotZ = 0;
    // The distance between the object and the viewer
    double k2 = 800;    
    // The distance between the object and the screen
    double k1 = 700;    
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
    const vector<vector<int>> modelVert = block.getVert();
    // The model's original triangles, should not be changed
    const vector<vector<int>> modelTri = block.getTri();
    // The buffer verticies for the block, represents the actual coord of the model in the 3d space 
    vector<vector<int>> blockVert = block.getVert(); 
    // The buffer triangles for the block, represents the actual coord of the model in the 3d space 
    vector<vector<int>> blockTri = block.getTri();
    // The buffer coordinates of the model on a 2D screen.
    vector<vector<int>> screenVert(blockVert.size(), vector<int> (2));

    // cout << "Block Verticies: " << endl;
    // for (int i = 0; i < blockVert.size(); i++) {
    //     for (int j = 0; j < blockVert.at(i).size(); j++) {
    //         cout << blockVert.at(i).at(j) << " ";
    //     }
    //     cout << endl;
    // }

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
            vector<int> temp = rotation(blockVert.at(i), rotX, rotY, rotZ);
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
            buff[0 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).at(0) - 1).at(0),
                                                (float)screenVert.at(blockTri.at(i).at(0) - 1).at(1));
            buff[1 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).at(1) - 1).at(0),
                                                (float)screenVert.at(blockTri.at(i).at(1) - 1).at(1));

            buff[2 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).at(1) - 1).at(0),
                                                (float)screenVert.at(blockTri.at(i).at(1) - 1).at(1));
            buff[3 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).at(2) - 1).at(0),
                                                (float)screenVert.at(blockTri.at(i).at(2) - 1).at(1));

            buff[4 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).at(2) - 1).at(0),
                                                (float)screenVert.at(blockTri.at(i).at(2) - 1).at(1));
            buff[5 + i * 6].position = Vector2f((float)screenVert.at(blockTri.at(i).at(1) - 1).at(0),
                                                (float)screenVert.at(blockTri.at(i).at(1) - 1).at(1));                                           
        }

        // clear the window with black background
        window.clear(sf::Color::Black);

        // draw & display stuff
        window.draw(buff);
        window.display();

        // Update the rotation angle
        if (!pause) {
            rotX += 0.01;
            rotY += 0.01;
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

vector<int> rotation(vector<int> vert, double rotX, double rotY, double rotZ) {
    vector<int> result = {0, 0, 0};
    int x = vert.at(0), y = vert.at(1), z = vert.at(2);
    rotX *= M_PI / 180;
    rotY *= M_PI / 180;
    rotZ *= M_PI / 180;
    double sRotX = std::sin(rotX), sRotY = std::sin(rotY), sRotZ = std::sin(rotZ);
    double cRotX = std::cos(rotX), cRotY = std::cos(rotY), cRotZ = std::cos(rotZ);

    result.at(0) = (x * cRotX * cRotY) + (y * sRotX * cRotY) - (z * sRotY);
    result.at(1) = (x * (cRotX * sRotY * sRotZ - sRotX * cRotZ)) + (y * (sRotX * sRotY * sRotZ + cRotX * cRotZ))
                    + (z * cRotY * sRotZ);
    result.at(2) = (x * (cRotX * sRotY * cRotZ + sRotX * sRotZ)) + (y * (sRotX * sRotY * cRotZ + cRotX * sRotZ))
                    + (z * cRotY * cRotZ);

    return result;
}

vector<int> projection(vector<int> vert, double k1, double k2, int width, int height) {
    vector<int> result(2, -1);
    int x = vert.at(0), y = vert.at(1), z = vert.at(2);

    result.at(0) = (k1 * x / (k2 + z)) + width / 2;
    result.at(1) = (k1 * y / (k2 + z)) + height / 2;

    // The 2D coordinates in the buffer is centered in the top left corner of the window
    // since the coordinate system in sfml window has the orgin in the top left. We have
    // to offset the points in the buffer by half of the width/height of the window
    return result;
}

