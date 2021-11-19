#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vec2d.h"
#include "Vec3d.h"
#include "Fps.cpp"
#include "ObjFileParser.h"
#include "3DModels/ObjModel.h"
#include "3DModels/Faces.h"
#include "util.h"

#define M_PI 3.14159265358979323846

using std::cout;
using std::endl;
using std::vector;
using sf::Color;
using sf::Uint8;
using sf::Vector2f;
using namespace util;

int main() {
    cout << "\nProgram Start.." << endl;

    // The width and height of the window
    // const int width = 1000, height = 700;
    const int width = 750, height = 500;
    // The rotation rate at each axis in degrees, default is 0
    float rotX = 0, rotY = 0, rotZ = 0;
    // The distance between the object and the viewer
    float k2 = 800.0;
    // The distance between the object and the screen
    float k1 = 700.0;
    // The camera's coordinates
    Vec3d camCord = {0.0, 0.0, -k2};
    // The position of the light source
    Vec3d lightCord = {300.0, -600.0, -700.0};
    // The base color of the surface of the object, (r, g, b)
    int baseRed = 255, baseGreen = 255, baseBlue = 255;
    // Ambient light intensity
    int ambientIntensity = 20;
    // the framerate/update rate
    int framerate = 144;
    // whether or not pause the game
    bool pause = true;
    // Keypress boolean 
    bool right = false, left = false, up = false, down = false;
    // Smooth angle threshold
    float smoothAngle = 15;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "Obj File Renderer", 
                                          sf::Style::Default, settings);
    window.setFramerateLimit(framerate);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { return EXIT_FAILURE; }
    sf::Text textInstruction;
    textInstruction.setFont(font);
    textInstruction.setString("Scroll Wheel up/down - Zoom in/out\nSpace - Pause/Play\nArrow Keys - Rotate Model");
    textInstruction.setCharacterSize(16);
    textInstruction.setFillColor(Color::White);
    textInstruction.setLineSpacing(1.2);
    textInstruction.setPosition(10, 10);

    FPS fps;

    // ObjModel block("ObjFiles/default_cube.obj", smoothAngle);
    // ObjModel block("ObjFiles/cone.obj", smoothAngle);
    // ObjModel block("ObjFiles/sphere.obj", smoothAngle);
    // ObjModel block("ObjFiles/torus.obj", smoothAngle);
    ObjModel block("ObjFiles/utah_teapot_final.obj", smoothAngle);

    // The model's original vertices, represents the actual coord of the model in the 3d space
    vector<Vec3d> blockVert = block.getVert();
    // The model's original triangles, represents the actual coord of the model in the 3d space
    vector<Faces> blockTri = block.getTri();
    // The model's vertex normals
    vector<Vec3d> blockVertNorm = block.getVertNorm();
    // The model's surface normal vectors
    vector<Vec3d> blockSurfNorm = block.getSurfNorm();
    // The model's surface normals' positions
    vector<Vec3d> blockSurfNormPos = block.getSurfNormPos();

    // The buffer vertices
    vector<Vec3d> vertices = block.getVert();
    // The buffer vertex normals
    vector<Vec3d> vertNorm = block.getVertNorm(); 
    // The buffer surface normals
    vector<Vec3d> surfNorm = block.getSurfNorm();
    // The buffer position of the surfNorm vertices
    vector<Vec3d> surfNormPos = block.getSurfNormPos();
    // The final buffer verticies that are facing the camera for transfering from 3d to 2d
    vector<Vec3d> facingCamVerts;
    // The triangle that faces the camera, will sort from the furthest to the cloest to the camera
    vector<Faces> facingCamTri;
    // The position of the surfNorm vertices that are facing the camera
    vector<Vec3d> facingSurfNormPos;

    // The final buffer that stores the color of the faces that are facing the camera
    vector<Color> facingVertColor; 
    // The buffer coordinates of the model on a 2D screen.
    vector<Vec2d> screenVert;

    sf::Texture texture;
    if (!texture.create(width, height)) {
        cout << "Error creating the texture" << endl;
        return -1;
    }
    texture.setSmooth(true);    
    sf::Sprite sprite(texture);

    // start the game loop
    while (window.isOpen()) {
        Uint8* pixels = new Uint8[width * height * 4];

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
                break;
            case (sf::Event::MouseWheelMoved):
                if (event.mouseWheel.delta < 0) {
                    for (int i = 0; i < vertices.size(); i++) {
                        blockVert.at(i) = blockVert.at(i) * 0.9;
                        blockSurfNormPos.at(i) = blockSurfNormPos.at(i) * 0.9;
                    }
                } else {
                    for (int i = 0; i < vertices.size(); i++) {
                        blockVert.at(i) = blockVert.at(i) * 1.1;
                        blockSurfNormPos.at(i) = blockSurfNormPos.at(i) * 1.1;
                    }
                }
                break;
            default:
                break;
            }
        }

        fps.update();
        window.setTitle("Obj File Renderer");
        sf::Text textFPS;
        textFPS.setFont(font);
        textFPS.setString("Fps: " + std::to_string(fps.getFPS()));
        textFPS.setCharacterSize(16);
        textFPS.setFillColor(Color::White);
        textFPS.setLineSpacing(1.2);
        textFPS.setPosition(width - 75, 20);

        // Do the rotation for the vertices
        for (int i = 0; i < blockVert.size(); i++) {
            vertices.at(i) = blockVert.at(i).rotation(rotX, rotY, rotZ);
        }
        for (int i = 0; i < blockVertNorm.size(); i++) {
            vertNorm.at(i) = blockVertNorm.at(i).rotation(rotX, rotY, rotZ);
        }
        for (int i = 0; i < blockSurfNorm.size(); i++) {
            surfNorm.at(i) = blockSurfNorm.at(i).rotation(rotX, rotY, rotZ);
        }
        for (int i = 0; i < blockSurfNormPos.size(); i++) {
            surfNormPos.at(i) = blockSurfNormPos.at(i).rotation(rotX, rotY, rotZ);
        }   // need this to calculate the distance between the face and the camera

        // calculate the facing of the triangles
        for (int i = 0; i < blockTri.size(); i++) {
            Vec3d centroid = surfNormPos.at(i);
            Vec3d dist = camCord - centroid;
            float dotProd = surfNorm.at(i).dot(dist);
            if (dotProd > 0) {
                facingCamTri.push_back(blockTri.at(i));
                facingSurfNormPos.push_back(surfNormPos.at(i));
            }
        }

        // quickSort the facingCamTri, painter's algorithm
        quickSort(facingSurfNormPos, facingCamTri, 0, facingCamTri.size() - 1, camCord);

        // store the faces' vertices into the facingCamVerts
        for (int i = 0; i < facingCamTri.size(); i++) {
            facingCamVerts.push_back(vertices.at(facingCamTri.at(i).vert1.x));
            facingCamVerts.push_back(vertices.at(facingCamTri.at(i).vert2.x));
            facingCamVerts.push_back(vertices.at(facingCamTri.at(i).vert3.x));
        }

        // Calculate the projection of the vertices in 3D space onto the screen
        for (int i = 0; i < facingCamVerts.size(); i++) {
            screenVert.push_back(facingCamVerts.at(i).projection(k1, k2, width, height));
        }

        // Goes through every single triangle, look through every pixel that is enclosed by the 
        // rectangle (which also encloses the triangle) and use the shoelace method to calculate the
        // weight of the normal and the position at each vertices to the specific pixel.
        for (int i = 0; i < screenVert.size(); i += 3) {
            Vec2d A = screenVert.at(i);                 // Here are the three points of the triangle
            Vec2d B = screenVert.at(i + 1);
            Vec2d C = screenVert.at(i + 2);
            int yMin = std::min({A.y, B.y, C.y});       // Here are the boundaries of the rectangle
            int yMax = std::max({A.y, B.y, C.y});       // that encloses the triangle 
            int xMin = std::min({A.x, B.x, C.x});
            int xMax = std::max({A.x, B.x, C.x});

            for (int y = yMin; y <= yMax; y++) {        // Calculate the lighting for each pixel in  
                for (int x = xMin; x <= xMax; x++) {    // the enclosed rectangle
                    int index = coordToIndex(x, y, width, height);
                    if (index != -1) {
                        float ABC = calcArea(A, B, C);
                        Vec2d P = Vec2d(x, y);
                        float alpha = calcArea(P, B, C) / ABC;
                        float beta = calcArea(A, P, C) / ABC;
                        float gamma = calcArea(A, B, P) / ABC;
                        if (alpha > 0 && beta > 0 && gamma > 0) {   // if the pixel is in the rectangle
                            Vec3d posA = facingCamVerts.at(i);          // The pos at each vertex
                            Vec3d posB = facingCamVerts.at(i + 1);
                            Vec3d posC = facingCamVerts.at(i + 2);
                            Faces currFace = facingCamTri.at(i / 3);
                            Vec3d normA = vertNorm.at(currFace.vert1.z);// The normal at each vertex
                            Vec3d normB = vertNorm.at(currFace.vert2.z);
                            Vec3d normC = vertNorm.at(currFace.vert3.z);
                            Vec3d pPos = posA * alpha + posB * beta + posC * gamma;
                            Vec3d pNorm = normA * alpha + normB * beta + normC * gamma;
                            float flux = (lightCord - pPos).dot(pNorm);
                            flux = flux / (lightCord - pPos).length() / pNorm.length();
                            Uint8 r, g, b;
                            r = clip(baseRed * flux, 0, 255);
                            g = clip(baseGreen * flux, 0, 255);
                            b = clip(baseBlue * flux, 0, 255);
                            pixels[index] = clip(r + ambientIntensity, 0, 255);
                            pixels[index + 1] = clip(g + ambientIntensity, 0, 255);
                            pixels[index + 2] = clip(b + ambientIntensity, 0, 255);
                            pixels[index + 3] = 255;
                        }
                    }
                }
            }        
        }

        texture.update(pixels);
        window.clear(Color::Black);
        window.draw(sprite);
        window.draw(textInstruction);
        window.draw(textFPS);
        window.display();

        // // clear all the buffer vertices and faces
        facingSurfNormPos.clear();
        facingCamTri.clear();
        facingCamVerts.clear();
        facingVertColor.clear();
        screenVert.clear();
        delete[] pixels;

        // Update the rotation angle
        if (!pause) {
            rotX -= 0.04;
            rotY += 0.5;
            // rotZ += 0.3;
        }
        // if (up) { rotX += 5; }
        // if (down) { rotX -= 5; }
        // if (left) { rotY -= 5; }
        // if (right) { rotY += 5; }
        if (up) { rotX += 1.5; }
        if (down) { rotX -= 1.5; }
        if (left) { rotY -= 1.5; }
        if (right) { rotY += 1.5; }
    }

    cout << "..Finished\n" << endl;
    return EXIT_SUCCESS;
}

