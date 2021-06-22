all: compile link

test: compile link run

compile:
	g++ -I src/include -c Fps.cpp Vec3d.cpp Vec2d.cpp ObjFileParser.cpp 3DModels/ObjModel.cpp Main.cpp  

link:
	g++ Main.o ObjFileParser.o Fps.o Vec3d.o Vec2d.o ObjModel.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system

clean:
	del *.o

run: 
	main.exe