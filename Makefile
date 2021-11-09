all: compile link

test: compile link run

compile:
	g++ -O1 -I src/include -c Fps.cpp Vec3d.cpp Vec2d.cpp util.cpp ObjFileParser.cpp 3DModels/ObjModel.cpp Main.cpp 

link:
	g++ -O1 Main.o ObjFileParser.o util.o Fps.o Vec3d.o Vec2d.o ObjModel.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system

clean:
	del *.o

run: 
	main.exe