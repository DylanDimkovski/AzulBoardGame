#include "Player.h"

Player::Player(std::string name) : Player(name, 0, new Mosaic())
{}

Player::Player(std::string name, int score, Mosaic *mosaic) : name(name), score(score), mosaic(mosaic)
{}

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
