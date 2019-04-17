#include "Player.h"
#include <array>
#include <math.h>
#include <iostream>

Player::Player()
{
    this->playerPosition = {0.0, 0.0, 0.0};
    this->playerXSize = 0;
    this->playerYSize = 0;
    this->playerZSize = 0;
}
Player::Player(std::array<float, 3> playerInitialPosition, float playerXSize, float playerYSize, float playerZSize, Maze *maze)
{
    this->playerPosition = playerInitialPosition;
    this->playerXSize = playerXSize;
    this->playerYSize = playerYSize;
    this->playerZSize = playerZSize;
    this->maze = maze;
}
std::array<float, 3> Player::getPlayerPosition()
{
    return this->playerPosition;
}
std::array<float, 3> Player::getPlayerMaxPosition()
{
    return {this->playerPosition[0] + playerXSize, this->playerPosition[1] + playerYSize, this->playerPosition[2] + playerZSize};
}
void Player::playerMove(int i)
{
    switch (i % 4)
    {
    case 0:
    {
        // get material location
        int x = maze->getColumnCount() - (int)round((playerPosition[0] + .5) * maze->getColumnCount());
        int y = (int)round((playerPosition[2] + .5) * maze->getRowCount()) - 1;
        std::cout << "maze: \"" << maze->getBlockMaterial(x, y) << "\"" << std::endl;
        if (maze->getBlockMaterial(x, y) == ' ')
        {
            playerPosition[2] += playerMoveSpeed;
        }
        break;
    }
    case 1:
    {
        int x = maze->getColumnCount() - (int)round((playerPosition[0] + .5) * maze->getColumnCount());
        int y = (int)round((playerPosition[2] + .5) * maze->getRowCount())+1;
        std::cout << "maze: \"" << maze->getBlockMaterial(x, y) << "\"" << std::endl;
        if (maze->getBlockMaterial(x, y) == ' ')
        {
            playerPosition[0] += playerMoveSpeed;
        }
        break;
    }
    case 2:
    {
        int x = maze->getColumnCount() - (int)round((playerPosition[0] + .5) * maze->getColumnCount());
        int y = (int)round((playerPosition[2] + .5) * maze->getRowCount());
        std::cout << "x: " << x << "y: " << y << std::endl;
        std::cout << "maze: \"" << maze->getBlockMaterial(x, y) << "\"" << std::endl;
        if (maze->getBlockMaterial(x, y) == ' ')
            playerPosition[2] -= playerMoveSpeed;
        break;
    }
    case 3:
    {
        int x = maze->getColumnCount() - (int)round((playerPosition[0] + .5) * maze->getColumnCount());
        int y = (int)round((playerPosition[2] + .5) * maze->getRowCount()) - 1;
        std::cout << "maze: \"" << maze->getBlockMaterial(x, y) << "\"" << std::endl;
        if (maze->getBlockMaterial(x, y) == ' ')
            playerPosition[0] -= (playerMoveSpeed);
        break;
    }
    default:
        break;
    }
}
void Player::moveForwards()
{
    playerMove(forwardIndex);
}
void Player::moveRight()
{
    playerMove(forwardIndex + 1);
}
void Player::moveBackwards()
{
    playerMove(forwardIndex + 2);
}
void Player::moveLeft()
{
    playerMove(forwardIndex + 3);
}
void Player::turnLeft()
{
    if (forwardIndex == 0)
    {
        forwardIndex = 3;
    }
    else
    {
        forwardIndex--;
    }
}

void Player::turnRight()
{
    forwardIndex = (forwardIndex + 1) % 4;
}