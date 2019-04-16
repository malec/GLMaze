ifeq ($(shell uname),Darwin)
LIB = -DMAC -framework OPENGL -framework GLUT
else
LIB = -lGL -lGLU -lglut
endif
CC = g++ -std=c++11

all:
	$(CC) project5.cpp Maze.cpp -o project5 $(LIB) libim/libim.a jpeg/libjpeg.a
clean:
	rm project5