#include "Player.h"

Player::Player(std::string name) : Player(name, 0, new Mosaic())
{
}

Player::Player(std::string name, int score, Mosaic *mosaic) : name(name), score(score), mosaic(mosaic)
{
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

std::vector<TileType> Player::calcScore()
{
    std::vector<TileType> toLid;
    for (int i = 0; i < NUMBER_OF_LINES; i++)
    {
        toLid.push_back(scoreLine(i));
    }
    return toLid;
}

TileType Player::scoreLine(int lineNum)
{
    TileType tile = NOTILE;
    int numTiles = getMosaic()->getLine(lineNum)->getNumTiles();
    if (getMosaic()->getLine(lineNum)->getMaxSize() == numTiles)
    {
        tile = getMosaic()->getLine(lineNum)->getTileType();
        getMosaic()->getLine(lineNum)->removeTiles();

        for (int i = 0; i < NUMBER_OF_LINES; i++)
        {
            if (master_wall[lineNum][i] == tile)
            {
                mosaic->setFilled(lineNum, i, true);
            }
        }
    }
    return tile;
}

Mosaic *Player::getMosaic()
{
    return mosaic;
}
