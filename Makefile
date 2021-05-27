all: compile link

test: compile link run

compile:
	g++ -I src/include -c Fps.cpp ObjFileParser.cpp PrimitiveModels/Cube.cpp PrimitiveModels/Pyramid.cpp PrimitiveModels/ObjModel.cpp Main.cpp  

link:
	g++ Main.o ObjFileParser.o Fps.o ObjModel.o Cube.o Pyramid.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system

clean:
	del *.o

run: 
	main.exe