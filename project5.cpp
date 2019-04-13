#include <string>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Maze.h"

void display() {

}

void keyboard(unsigned char key, int x, int y) {

}

void mouseFunc(int button, int state, int x, int y) {

}

void init() {

}

int main(int argc, char* argv[]) {
	Maze maze = Maze();
	const auto mazeFileName = "maze.txt";
	maze.readMazeFile(mazeFileName);
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 250);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutCreateWindow("Maze");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseFunc);
	init();
	return 0;
}