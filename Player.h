#include <vector>
#include <array>

class Player {
    public:
        Player();
        Player(std::array<float, 3> playerInitialPosition, float playerXSize, float playerYSize, float playerZSize);
        std::array<float, 3> getPlayerPosition();
        std::array<float, 3> getPlayerMaxPosition();
        void moveLeft();
        void moveRight();
        void moveForwards();
        void moveBackwards();
    	float playerMoveSpeed = .0625;
    private:
        std::array<float, 3> playerPosition;
        float playerXSize;
        float playerYSize;
        float playerZSize;
};