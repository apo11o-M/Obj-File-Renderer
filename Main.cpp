#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Fps.cpp"
#include "Cube.h"

using std::vector;

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
    // The width and height of the window
    const int width = 1000, height = 700;
    // The rotation rate at each axis in degrees, default is 0
    double rotX = 0, rotY = 0, rotZ = 0;
    // The distance between the object and the viewer
    double k2 = 800;
    // The distance between the object and the screen
    double k1 = 700;
    

    sf::RenderWindow window(sf::VideoMode(width, height), "Bruh the window is showing stuff");
    window.setFramerateLimit(144);
    FPS fps;
    
    Cube block;
    // Get the verticies and the triangles from the cube
    vector<vector<int>> blockVert = block.getVert(); 
    vector<vector<int>> blockTri = block.getTri();
    vector<vector<int>> screenVert(blockVert.size(), vector<int> (2));

    // The buff vertex array stores all the lines that we will be drawing, the reason why we multiply
    // by six is because we need 6 points to draw 3 lines
    sf::VertexArray* buff = new sf::VertexArray(sf::Lines, blockTri.size() * 6);

    // start the game loop
    while (window.isOpen()) {

        // Event handlers
        sf::Event event;
        while (window.pollEvent(event)) {
            // check to close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // update the window's title to the current frame per second
        fps.update();
        window.setTitle("Dude the window is showing stuff, Fps: " 
                        + std::to_string(fps.getFPS()));
    
        // calculate the rotation and the projection of the 3D verticies, and store
        // the 2D points in a vector
        for (int i = 0; i < blockVert.size(); i++) {
            vector<int> temp = rotation(blockVert.at(i), rotX, rotY, rotZ);
            screenVert.at(i) = projection(temp, k1, k2, width, height);
            //std::cout << "Coord: " << screenVert.at(i).at(0) << ", " << screenVert.at(i).at(1) << std::endl;
        }

        // store the verticies into the buffer using the blockTri that shows the vertices to use
        // for triangles, we would need a total of 3 lines, or 6 points for each arragements 
        // (point 1-2, 2-3, 1-3). And yes the order of which we insert the vertex object matters since the 
        // buffer uses it to connect the lines
        for (int i = 0; i < blockTri.size(); i++) {
            // buff->append(sf::Vertex(sf::Vector2f(screenVert.at(i).at(0), screenVert.at(i).at(1))));
            buff->append(sf::Vertex(sf::Vector2f(
                    screenVert.at(blockTri.at(i).at(0)).at(0),
                    screenVert.at(blockTri.at(i).at(0)).at(1)
            )));
            for (int j = 1; j < blockTri.at(i).size(); j++) {
                buff->append(sf::Vertex(sf::Vector2f(
                    screenVert.at(blockTri.at(i).at(j)).at(0),
                    screenVert.at(blockTri.at(i).at(j)).at(1)
                )));
                buff->append(sf::Vertex(sf::Vector2f(
                    screenVert.at(blockTri.at(i).at(j)).at(0),
                    screenVert.at(blockTri.at(i).at(j)).at(1)
                )));
            }
            buff->append(sf::Vertex(sf::Vector2f(
                screenVert.at(blockTri.at(i).at(0)).at(0),
                screenVert.at(blockTri.at(i).at(0)).at(1)
            ))); 
        }

        // clear the window with black background
        window.clear(sf::Color::Black);

        // draw & display stuff
        window.draw(*buff);
        window.display();

        // clear our buff
        buff->clear();

        // Update the rotation angle
        rotX += 0.1;
        rotY += 0.3;
        //rotZ += 0.3;
    }

    delete buff;
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

