#include <string>
#include <vector>
#include <array>

class Maze {
public:
	Maze();
	void readMazeFile(std::string fileName);
	int getColumnCount();
	int getRowCount();
	float getBlockXSize();
	float getBlockYSize();
	float getBlockZSize();
	char getBlockMaterial(int x, int y);
	std::array<float, 3> getInitialPosition();
	~Maze();
private:
	const int headerLineCount = 2;
	int rowCount;
	int columnCount;
	int startRow;
	int startColumn;
	std::vector<std::vector<char>> maze;
};

