#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Fps.cpp"
#include "PrimitiveModels/Pyramid.h"
#include "PrimitiveModels/Cube.h"
#include "PrimitiveModels/ObjModel.h"
#include "PrimitiveModels/Faces.h"
#include "ObjFileParser.h"
#include "Vec2d.h"
#include "Vec3d.h"

#define M_PI 3.14159265358979323846

using std::vector;
using std::cout;
using std::endl;
using sf::Vector2f;

void bufferFill();

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
    // The camera's coordinates
    Vec3d camCord = {0, 0, -k2};
    // the framerate/update rate
    int framerate = 144;
    // whether or not pause the game
    bool pause = true;
    bool right = false, left = false, up = false, down = false;

    sf::RenderWindow window(sf::VideoMode(width, height), "yo the window is showing stuff");
    window.setFramerateLimit(framerate);
    FPS fps;
    
    // ObjModel block("ObjModelFiles/default_cube.obj");
    ObjModel block("ObjModelFiles/cone.obj");
    // ObjModel block("ObjModelFiles/utah_teapot_resized.obj");

    // // The model's original vertices, should not be changed 
    // const vector<Vec3d> modelVert = block.getVert();
    // // The model's original triangles, should not be changed
    // const vector<Faces> modelTri = block.getTri();
    // // The model's original triangles, should not be changed
    // const vector<Vec3d> modelSurfNorm = block.getSurfNorm();

    // The buffer vertices for the block, represents the actual coord of the model in the 3d space 
    vector<Vec3d> blockVert = block.getVert(); 
    // The buffer triangles for the block, represents the actual coord of the model in the 3d space 
    vector<Faces> blockTri = block.getTri();
    // The model's surface normals
    vector<Vec3d> blockSurfNorm = block.getSurfNorm();     
    
    // The buffer vertices for the block
    vector<Vec3d> newVert = block.getVert();
    // The buffer surface normals for the block
    vector<Vec3d> newSurfNorm = block.getSurfNorm();
    // The final verticies that are facing the camera for transfering from 3d to 2d
    vector<Vec3d> facingCamVerts;

    // The buffer coordinates of the model on a 2D screen.
    // vector<Vec2d> screenVert(blockVert.size(), Vec2d());
    vector<Vec2d> screenVert;
    screenVert.reserve(blockVert.size());

    // The buff vertex array stores all the lines that we will be drawing, the reason 
    // why we multiply by six is because we need 6 points to draw 3 lines
    // sf::VertexArray buff(sf::Lines, blockTri.size() * 6);
    sf::VertexArray buff(sf::Lines, 0);


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

        // calculate the rotation for each surface normals
        for (int i = 0; i < blockSurfNorm.size(); i++) {
            newSurfNorm.at(i) = blockSurfNorm.at(i).rotation(rotX, rotY, rotZ);
        }

        // calculate the rotation for each vertices
        for (int i = 0; i < blockVert.size(); i++) {
            newVert.at(i) = blockVert.at(i).rotation(rotX, rotY, rotZ);
        }

        // calculate the facing of those faces, if a face is facing towards us, add its verticies
        // to the array to calculate the projection
        for (int i = 0; i < blockTri.size(); i++) {
            double dotProduct = newSurfNorm.at(i).dot(camCord);
            if (dotProduct > 0) {
                facingCamVerts.push_back(newVert.at(blockTri.at(i).vert1.x));
                facingCamVerts.push_back(newVert.at(blockTri.at(i).vert2.x));
                facingCamVerts.push_back(newVert.at(blockTri.at(i).vert3.x));
            }
        }
        
        // calculate the projection of the 3d verticies
        for (int i = 0; i < facingCamVerts.size(); i++) {
            screenVert.push_back(facingCamVerts.at(i).projection(k1, k2, width, height));
        }
        
        // store the 2D verticies that we calculated from the previous rotation and projection 
        // calculation into the buffer so the SFML knows what to draw. Use the blockTri that shows
        // the vertices that forms the triangles, we would need a total of 3 lines, or 6 points 
        // for each arragements (point 1-2, 2-3, 3-1). And yes the order of which we insert the 
        // vertex object matters since the buffer uses those points to connect the lines
        for (int i = 0; (i + 3) < screenVert.size(); i += 3) {
            buff.append(Vector2f(static_cast<float>(screenVert.at(i).x), 
                                 static_cast<float>(screenVert.at(i).y)));
            buff.append(Vector2f(static_cast<float>(screenVert.at(i + 1).x), 
                                 static_cast<float>(screenVert.at(i + 1).y)));
            
            buff.append(Vector2f(static_cast<float>(screenVert.at(i + 1).x), 
                                 static_cast<float>(screenVert.at(i + 1).y)));
            buff.append(Vector2f(static_cast<float>(screenVert.at(i + 2).x), 
                                 static_cast<float>(screenVert.at(i + 2).y)));
                            
            buff.append(Vector2f(static_cast<float>(screenVert.at(i + 2).x), 
                                 static_cast<float>(screenVert.at(i + 2).y)));
            buff.append(Vector2f(static_cast<float>(screenVert.at(i).x), 
                                 static_cast<float>(screenVert.at(i).y)));
        }
                // cout << "   screenVert.size(): " << screenVert.size() << endl;
                // cout << "   buff.getVertexCount(): " << buff.getVertexCount() << endl;

        // clear the window with black background
        window.clear(sf::Color::Black);
        // draw & display stuff
        window.draw(buff);
        window.display();

        // clear the facing cam vert
        facingCamVerts.clear();
        // clear the screenVert so we can redo that again in the next loop
        screenVert.clear();
        // clear the buffer so the canvas is clean
        buff.clear();
        
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

    cout << "..Finished\n" << endl;
    return 0;
}