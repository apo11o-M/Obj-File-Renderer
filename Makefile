all: compile link

compile:
	g++ -I src/include -c Fps.cpp Cube.cpp Main.cpp 
link:
	g++ Main.o Cube.o Fps.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system

