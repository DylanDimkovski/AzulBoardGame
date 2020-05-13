#include "Player.h"

Player::Player(std::string name, int score) : Player(name, new Mosaic(), score)
{
}

Player::Player(std::string name, Mosaic *mosaic, int score) : name(name), score(score)
{
    this->mosaic = mosaic;
}

Player::~Player()
{
    delete mosaic;
}

std::string Player::getName()
{
    return name;
}

int Player::getScore()
{
    return score;
}

void Player::calcScore()
{
    // TODO implement
}

Mosaic *Player::getMosaic()
{
    return mosaic;
}
