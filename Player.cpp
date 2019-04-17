#include "Player.h"
#include <array>
Player::Player()
{
    this->playerPosition = {0.0, 0.0, 0.0};
    this->playerXSize = 0;
    this->playerYSize = 0;
    this->playerZSize = 0;
}
Player::Player(std::array<float, 3> playerInitialPosition, float playerXSize, float playerYSize, float playerZSize)
{
    this->playerPosition = playerInitialPosition;
    this->playerXSize = playerXSize;
    this->playerYSize = playerYSize;
    this->playerZSize = playerZSize;
}
std::array<float, 3> Player::getPlayerPosition()
{
    return this->playerPosition;
}
std::array<float, 3> Player::getPlayerMaxPosition()
{
    return {this->playerPosition[0] + playerXSize, this->playerPosition[1] + playerYSize, this->playerPosition[2] + playerZSize};
}
void Player::moveForwards() {
    playerPosition[2] += playerMoveSpeed * direction;
}
void Player::moveRight() {
    playerPosition[0] += (playerMoveSpeed * direction);
}
void Player::moveBackwards() {
    playerPosition[2] -= playerMoveSpeed * direction;
}
void Player::moveLeft() {
    playerPosition[0] -= (playerMoveSpeed * direction);
}
void Player::turnLeft() {
    this->direction = (this->forwardIndex == 2 ? this->forwardIndex * -1 : this->forwardIndex);
    this-> forwardIndex = (this->forwardIndex == 2 ? 0 : 2);
}

void Player::turnRight() {
    this->direction = (this->forwardIndex == 0 ? this->forwardIndex * -1 : this->forwardIndex);
    this-> forwardIndex = (this->forwardIndex == 2 ? 0 : 2);
}