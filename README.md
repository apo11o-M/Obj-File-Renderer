# Obj File Renderer

<!-- ![Obj_File_Renderer_Demo](https://user-images.githubusercontent.com/54286072/123527089-87178680-d691-11eb-9a35-92b0945c0e0d.gif) -->
![Obj_File_Renderer_Demo2](https://user-images.githubusercontent.com/54286072/124899745-4541e680-df95-11eb-939c-2e20ecdff6d2.gif)

## What is this?
Obj File Renderer is a program that renders OBJ files to a 2D display using C++ and the SFML Library. In other words, it reads in a 3D model file that consists of the vertices and the faces data of the 3D model, do some fancy rotations, calculate the lighting of each individual faces, then project those points onto the 2D screen.

I decided to write every mathematics part from the ground up based on my understanding of linear algebra and lots of digging through the internet. And I use the SFML library to handle the actual drawing of the triangles.

Currently I am still experimenting with the concept so it still has limited features. In the future I will be constantly adding more stuff such as moveable camera and smoother lighting on the model.

## Credits

- Originally inspired by the Japanese Minecraft player EMB4 who created the MCHeli Minecraft Mod using .obj 3D models for the vehicles, link to the website: https://www.curseforge.com/minecraft/mc-mods/mcheli-minecraft-helicopter-mod.
- Also Inspired by Andy Sloane from his Donut C program, link to his website: https://www.a1k0n.net/2011/07/20/donut-math.html.
- Massive thanks for professor Craig Schroeder for guiding me and clarifying some confusions I have about the 3D rendering pipeline.

## Major Updates

### 7/8/2021
- Implemented the Gouraud Shading algorithm so the surfaces looks smoother. The color at each pixel is the combined weight of each color at the triangles' vertices.
- Reworked on how SFML renders the object.

<!-- ![07082021 Gouraud Shading](https://user-images.githubusercontent.com/54286072/124899366-e4b2a980-df94-11eb-8ec5-265bae4226a0.gif) -->
<img src="https://user-images.githubusercontent.com/54286072/124899366-e4b2a980-df94-11eb-8ec5-265bae4226a0.gif" width="504" height="354"> <br />


### 6/26/2021
- Added lighting to the surfaces (flat shading), the calculation is based on the angle between the individual faces with respect to the light source using dot product.

<!-- ![06262021 Basic Lighting](https://user-images.githubusercontent.com/54286072/123527859-d791e280-d697-11eb-924b-b595f573cde3.gif) <br /> -->
<img src="https://user-images.githubusercontent.com/54286072/123527859-d791e280-d697-11eb-924b-b595f573cde3.gif" width="504" height="354"> <br />


### 6/25/2021
- Uses painter's algorithm so the front-facing faces that are behind others will be covered. So the model is not see-through anymore.

<!-- ![06252021 Painter's Algorithm](https://user-images.githubusercontent.com/54286072/123527862-d9f43c80-d697-11eb-99ab-feeda77beb76.gif) <br /> -->
<img src="https://user-images.githubusercontent.com/54286072/123527862-d9f43c80-d697-11eb-99ab-feeda77beb76.gif" width="504" height="354"> <br />


### 6/12/2021
- Uses the surface normals to calculate the angle between the individual faces and the camera, so now only the faces that are facing the camera (instead of all of the faces) will be rendered.
- However, this also means that some faces that are facing towards the camera but are behind other front-facing faces will also get rendered.

<!-- ![06112021 Back Face Culling 2](https://user-images.githubusercontent.com/54286072/123529459-33af3380-d6a5-11eb-87c1-2b906a10112b.gif) -->
<img src="https://user-images.githubusercontent.com/54286072/123529459-33af3380-d6a5-11eb-87c1-2b906a10112b.gif" width="504" height="354"> <br />


### 5/27/2021
- Added a obj file parser to read in the data from the file and format it into something the program can use.
- Refractered the code into using custom Vec3d and Vec2d classes instead of 2d arrays, so the code looks cleaner and more scalable.

<!-- ![05022021 Cone Demo](https://user-images.githubusercontent.com/54286072/123527654-16269d80-d696-11eb-839a-501df9ed50e1.gif) <br /> -->
<img src="https://user-images.githubusercontent.com/54286072/123527654-16269d80-d696-11eb-839a-501df9ed50e1.gif" width="504" height="354"> <br />


### 4/28/2021
- Hard coded some simple 3D objects to test out the algorithm.
- Updated the method for inserting the vertices into the buffer.

<!-- ![04032021 Box Demo](https://user-images.githubusercontent.com/54286072/123527640-fdb68300-d695-11eb-9acd-260d2e26444b.gif) <br /> -->
<img src="https://user-images.githubusercontent.com/54286072/123527640-fdb68300-d695-11eb-9acd-260d2e26444b.gif" width="504" height="354"> <br />


### 4/2/2021 ~ 4/5/2021
- Migrated the 3D model renderer from my previous python project "Simple3DModelRenderer" to here using C++ and SFML library for faster speed.
- The ideas are the same, do the rotation for the 3D points, then project those 3D points onto a 2D screen 
