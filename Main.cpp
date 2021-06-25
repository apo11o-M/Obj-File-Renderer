#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Vec2d.h"
#include "Vec3d.h"
#include "Fps.cpp"
#include "ObjFileParser.h"
#include "3DModels/ObjModel.h"
#include "3DModels/Faces.h"
// #include "3DModels/Pyramid.h"
// #include "3DModels/Cube.h"

#define M_PI 3.14159265358979323846

using std::cout;
using std::endl;
using std::vector;
using sf::Color;
using sf::Vector2f;

void quickSort(vector<Vec3d> &arr, vector<Faces> &target, int low, int high, Vec3d &camPos);
int partition(vector<Vec3d> &arr, vector<Faces> &target, int low, int high, Vec3d &camPos);
void swap(Vec3d &a, Vec3d &b);

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
    
    // ObjModel block("ObjFiles/default_cube.obj");
    // ObjModel block("ObjFiles/cone.obj");
    // ObjModel block("ObjFiles/sphere.obj");
    ObjModel block("ObjFiles/torus.obj");
    // ObjModel block("ObjFiles/utah_teapot_resized.obj");


    // The model's original vertices, represents the actual coord of the model in the 3d space
    vector<Vec3d> blockVert = block.getVert();
    // The model's original triangles, represents the actual coord of the model in the 3d space
    vector<Faces> blockTri = block.getTri();
    // The model's surface normal vectors
    vector<Vec3d> blockSurfNorm = block.getSurfNorm();
    // The model's surface normals' positions
    vector<Vec3d> blockSurfNormPos = block.getSurfNormPos();

    // The buffer vertices for the block
    vector<Vec3d> vertices = block.getVert();
    // The buffer surface normals for the block
    vector<Vec3d> surfNorm = block.getSurfNorm();
    // The buffer position of the surfNorm vertices
    vector<Vec3d> surfNormPos = block.getSurfNormPos();
    // The triangle that faces the camera, will sort from the furthest to the cloest to the camera
    vector<Faces> facingCamTri;
    // The final buffer verticies that are facing the camera for transfering from 3d to 2d
    vector<Vec3d> facingCamVerts;
    // The position of the surfNorm vertices that are facing the camera
    vector<Vec3d> facingSurfNormPos;

    // The buffer coordinates of the model on a 2D screen.
    vector<Vec2d> screenVert;

    // The buff vertex array stores all the lines that we will be drawing
    sf::VertexArray buffLine(sf::Lines, 0);
    sf::VertexArray buffTri(sf::Triangles, 0);


    // start the game loop
    while (window.isOpen()) {
        // Event handlers
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case (sf::Event::Closed):
                window.close();
                break;
            case (sf::Event::KeyPressed):
                if (event.key.code == sf::Keyboard::Space) { pause = !pause; }
                else if (event.key.code == sf::Keyboard::Up) { up = true; }
                else if (event.key.code == sf::Keyboard::Down) { down = true; }
                else if (event.key.code == sf::Keyboard::Left) { left = true; }
                else if (event.key.code == sf::Keyboard::Right) { right = true; }
                else if (event.key.code == sf::Keyboard::Escape) { window.close(); }
                break;
            case (sf::Event::KeyReleased):
                if (event.key.code == sf::Keyboard::Up) { up = false; }
                else if (event.key.code == sf::Keyboard::Down) { down = false; }
                else if (event.key.code == sf::Keyboard::Left) { left = false; }
                else if (event.key.code == sf::Keyboard::Right) { right = false; }
            default:
                break;
            }
        }

        // update the window's title to the current frame per second
        fps.update();
        window.setTitle("yo the window is showing stuff, Fps: " + std::to_string(fps.getFPS()));

        // calculate the rotation for each vertices
        for (int i = 0; i < blockVert.size(); i++) {
            vertices.at(i) = blockVert.at(i).rotation(rotX, rotY, rotZ);
        }
        // calculate the rotation for each surface normals
        for (int i = 0; i < blockSurfNorm.size(); i++) {
            surfNorm.at(i) = blockSurfNorm.at(i).rotation(rotX, rotY, rotZ);
        }
        // calculate the rotation for each surface normal's position
        for (int i = 0; i < blockSurfNormPos.size(); i++) {
            surfNormPos.at(i) = blockSurfNormPos.at(i).rotation(rotX, rotY, rotZ);
        }
        // calculate the facing of those faces, if a face is facing towards us, add its verticies
        // to the array to calculate the projection
        for (int i = 0; i < blockTri.size(); i++) {
            Vec3d centroid = surfNormPos.at(i);
            Vec3d temp = camCord - centroid;
            double dotProduct = surfNorm.at(i).dot(temp);
            if (dotProduct > 0) {
                facingCamTri.push_back(blockTri.at(i));
                facingSurfNormPos.push_back(surfNormPos.at(i));
            }
        }
        
        // sort the faces and the position of the surface normals so the one that is cloest to the 
        // camera will be at the start of the vector
        quickSort(facingSurfNormPos, facingCamTri, 0, facingCamTri.size() - 1, camCord);

        // reverse the order of the faces and store the vertices to the buffer. So the face that is 
        // furthest from the camera will be drawn first.
        for (int i = facingCamTri.size() - 1; i >= 0; i--) {
            facingCamVerts.push_back(vertices.at(facingCamTri.at(i).vert1.x));
            facingCamVerts.push_back(vertices.at(facingCamTri.at(i).vert2.x));
            facingCamVerts.push_back(vertices.at(facingCamTri.at(i).vert3.x));
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
        for (int i = 0; (i + 2) < screenVert.size(); i += 3) {
            buffLine.append(Vector2f(static_cast<float>(screenVert.at(i).x),
                                     static_cast<float>(screenVert.at(i).y)));
            buffLine.append(Vector2f(static_cast<float>(screenVert.at(i + 1).x),
                                     static_cast<float>(screenVert.at(i + 1).y)));

            buffLine.append(Vector2f(static_cast<float>(screenVert.at(i + 1).x),
                                     static_cast<float>(screenVert.at(i + 1).y)));
            buffLine.append(Vector2f(static_cast<float>(screenVert.at(i + 2).x),
                                     static_cast<float>(screenVert.at(i + 2).y)));

            buffLine.append(Vector2f(static_cast<float>(screenVert.at(i + 2).x),
                                     static_cast<float>(screenVert.at(i + 2).y)));
            buffLine.append(Vector2f(static_cast<float>(screenVert.at(i).x),
                                     static_cast<float>(screenVert.at(i).y)));

            buffTri.append(Vector2f(static_cast<float>(screenVert.at(i).x),
                                    static_cast<float>(screenVert.at(i).y)));
            buffTri.append(Vector2f(static_cast<float>(screenVert.at(i + 1).x),
                                    static_cast<float>(screenVert.at(i + 1).y)));
            buffTri.append(Vector2f(static_cast<float>(screenVert.at(i + 2).x),
                                    static_cast<float>(screenVert.at(i + 2).y)));                           
        }
        
        // clear the window with black background
        window.clear(sf::Color::Black);

        // Draw the black triangle to cover the existing lines on the canvas and the white outline 
        // to show the triangle  
        for (int i = 0; i < buffTri.getVertexCount(); i += 3) {
            sf::VertexArray tempTri(sf::Triangles, 3);
            tempTri[0].position = Vector2f(buffTri[i].position.x, buffTri[i].position.y);
            tempTri[1].position = Vector2f(buffTri[i + 1].position.x, buffTri[i + 1].position.y);
            tempTri[2].position = Vector2f(buffTri[i + 2].position.x, buffTri[i + 2].position.y);
            tempTri[0].color = Color::Black;
            tempTri[1].color = Color::Black;
            tempTri[2].color = Color::Black;

            sf::VertexArray tempLine(sf::Lines, 6);                
            for (int j = 0; j < 6; j += 2) {
                tempLine[j].position = Vector2f(buffLine[i * 2 + j].position.x, 
                                                buffLine[i * 2 + j].position.y);
                tempLine[j + 1].position = Vector2f(buffLine[i * 2 + j + 1].position.x, 
                                                    buffLine[i * 2 + j + 1].position.y);
            }
            window.draw(tempTri);
            window.draw(tempLine);
        }

        window.display();

        // clear all the buffer vertices and faces
        facingCamVerts.clear();
        facingCamTri.clear();
        facingSurfNormPos.clear();
        screenVert.clear();
        // clear the buffer so the canvas is clean
        buffLine.clear();
        buffTri.clear();
        
        // Update the rotation angle
        if (!pause) {
            rotX += 0.1;
            rotY += 0.17;
            // rotZ += 0.3;
        }
        if (up) { rotX += 0.2; }
        if (down) { rotX -= 0.2; }
        if (left) { rotY -= 0.2; }
        if (right) { rotY += 0.2; }
    }

    cout << "..Finished\n" << endl;
    return 0;
}

void quickSort(vector<Vec3d> &arr, vector<Faces> &target, int low, int high, Vec3d &camPos) {
    if (low < high) {
        int pi = partition(arr, target, low, high, camPos);
        quickSort(arr, target, low, pi - 1, camPos);
        quickSort(arr, target, pi + 1, high, camPos);
    }
}

int partition(vector<Vec3d> &arr, vector<Faces> &target, int low, int high, Vec3d &camPos) {
    double pivot = arr.at(high).distanceSquared(camPos);
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr.at(j).distanceSquared(camPos) <= pivot) {
            i++;
            //swap arr[i] and arr[j]
            Vec3d temp = arr.at(j);
            arr.at(j) = arr.at(i);
            arr.at(i) = temp;
            Faces temp2 = target.at(j);
            target.at(j) = target.at(i);
            target.at(i) = temp2;
        }
    }
    // swap arr[i + 1], arr[high]
    Vec3d temp = arr.at(high);
    arr.at(high) = arr.at(i + 1);
    arr.at(i + 1) = temp;
    Faces temp2 = target.at(high);
    target.at(high) = target.at(i + 1);
    target.at(i + 1) = temp2;

    return (i + 1);
}
