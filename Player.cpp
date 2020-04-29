#include "Player.h"

Player::Player(std::string name) : Player(name, new Mosaic())
{}

Player::Player(std::string name, Mosaic* mosaic) : name(name)
{
    this->mosiac = mosaic;
}

Player::~Player()
{
    delete mosiac;
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
