#include "Player.h"

Player::Player(std::string name) : Player(name, 0, new Mosaic())
{}

Player::Player(std::string name, int score, Mosaic* mosaic) : 
    name(name), score(score), mosiac(mosaic)
{}

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
