LIB = -lGL -lGLU -lglut
CC = g++ -std=c++11

all:
	$(CC) project5.cpp Maze.cpp -o project5 -lGL -lGLU -lglut libim/libim.a jpeg/libjpeg.a
clean:
	rm project5