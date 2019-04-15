#pragma once
#include <string>
#include <vector>
class Maze {
public:
	Maze();
	void readMazeFile(std::string fileName);
	int getColumnCount();
	int getRowCount();
	float getBlockXSize();
	float getBlockZSize();
	~Maze();
private:
	const int headerLineCount = 2;
	int rowCount;
	int columnCount;
	int startRow;
	int startColumn;
	std::vector<std::vector<char>> maze;
};

