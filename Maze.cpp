#include "Maze.h"
#include <string>
#include <fstream>
#include <exception>
#include <iostream>

Maze::Maze()
{
}
int Maze::getRowCount()
{
	return this->rowCount;
}
int Maze::getColumnCount()
{
	return this->columnCount;
}
float Maze::getBlockXSize()
{
	return 1.0 / this->columnCount;
}
float Maze::getBlockZSize()
{
	return 1.0 / this->rowCount;
}
float Maze::getBlockYSize()
{
	return 0.125;
}
void Maze::readMazeFile(std::string fileName)
{
	std::ifstream fileStream(fileName);
	if (fileStream.is_open())
	{
		std::string line;
		int lineNumber = 0;
		while (std::getline(fileStream, line))
		{
			if (lineNumber == 0)
			{
				int splitIndex = line.find(' ');
				this->rowCount = std::stoi(line.substr(0, splitIndex));
				this->columnCount = std::stoi(line.substr(splitIndex + 1, line.length() - 1));
				maze.resize(rowCount);
				for (int i = 0; i < maze.size(); i++)
				{
					maze[i].resize(columnCount);
				}
			}
			else if (lineNumber == 1)
			{
				int splitIndex = line.find(' ');
				this->startRow = std::stoi(line.substr(0, splitIndex));
				this->startColumn = std::stoi(line.substr(splitIndex + 1, line.length() - 1));
			}
			else
			{
				for (int currentColumn = 0; currentColumn < columnCount; currentColumn++)
				{
					std::cout << "text: \"" << line[currentColumn] << "\"" <<std::endl;
					maze[lineNumber - headerLineCount][currentColumn] = line[currentColumn];
				}
			}
			lineNumber++;
		}
	}
	else
	{
		exit(1);
	}
}
char Maze::getBlockMaterial(int x, int y)
{
	if (x > getColumnCount() || y > getRowCount())
	{
		return 'b';
	}
	else
	{
		return this->maze[x][y];
	}
}
std::array<float, 3> Maze::getInitialPosition()
{
	return {(float)this->startColumn / (float)this->columnCount - .5, 0, (float)this->startRow / (float)this->rowCount + .5};
}
Maze::~Maze()
{
}
