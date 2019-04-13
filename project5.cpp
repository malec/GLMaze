#include <string>
#include <exception>
#include <fstream>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void readMazeFile() {
	const auto mazeFileName = "./maze.txt";
	std::ifstream fileStream(mazeFileName);
	if (fileStream.is_open()) {
		std::string line;
		int lineNumber = 0;
		while (std::getline(fileStream, line)) {
			if (lineNumber == 0) {
				// Get the number of rows
				// Get the number of columns
			}
			lineNumber++;
		}
	} else {
		throw std::exception("Could not open the file");
	}
}

int main() {
	readMazeFile();
	system("pause");
	return 0;
}