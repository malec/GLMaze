#include <string>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Maze.h"

int main() {
	Maze maze = Maze();
	const auto mazeFileName = "./maze.txt";
	maze.readMazeFile(mazeFileName);
	system("pause");
	return 0;
}