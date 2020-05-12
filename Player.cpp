#include "Player.h"

Player::Player(std::string name, int score) : Player(name, new Mosaic(), score)
{}

Player::Player(std::string name, Mosaic* mosaic, int score) : name(name), score(score)
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
