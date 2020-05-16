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
        int lineScore = scoreLine(i);
        if (lineScore > 0)
        {
            TileType tile = getMosaic()->getLine(i)->getTileType();
            toLid.push_back(tile);
            score += lineScore;
        }
    }
    return toLid;
}

int Player::scoreLine(int lineNum)
{
    int lineScore = 0;
    int numTiles = getMosaic()->getLine(lineNum)->getNumTiles();

    if (getMosaic()->getLine(lineNum)->getMaxSize() == numTiles)
    {
        TileType tile = getMosaic()->getLine(lineNum)->getTileType();
        getMosaic()->getLine(lineNum)->removeTiles();

        for (int i = 0; i < NUMBER_OF_LINES; i++)
        {
            if (master_wall[lineNum][i] == tile)
            {
                mosaic->setFilled(lineNum, i, true);

                int rowScore = calcRow(i, lineNum);
                if (rowScore > 0)
                {
                    lineScore += rowScore;
                }
                int colScore = calcCol(i, lineNum);
                if (colScore > 0)
                {
                    lineScore += colScore;
                }
                if (lineScore == 0)
                {
                    lineScore++;
                }
            }
        }
    }
    return lineScore;
}

int Player::calcRow(int index, int line)
{
    int score = 0;
    int pos = index + 1;

    do
    {
        if (mosaic->isFilled(line, pos) == true)
        {
            ++score;
        }
        ++pos;
    } while (pos + 1 < NUMBER_OF_LINES);

    pos = index - 1;
    do
    {
        if (mosaic->isFilled(line, pos) == true)
        {
            ++score;
        }
        --pos;
    } while (pos - 1 >= 0);

    return score;
}

int Player::calcCol(int index, int line)
{
    int score = 0;
    int pos = line + 1;

    do
    {
        if (mosaic->getWallLine(pos)[index] == true)
        {
            score++;
        }
        pos++;
    } while (pos + 1 < NUMBER_OF_LINES);

    pos = line - 1;
    do
    {
        if (mosaic->getWallLine(pos)[index] == true)
        {
            score++;
        }
        pos--;
    } while (pos - 1 >= 0);

    return score;
}

Mosaic *Player::getMosaic()
{
    return mosaic;
}

bool Player::hasWon()
{
    int line = 0;
    bool hasWon = false;
    while (!hasWon && line < NUMBER_OF_LINES)
    {
        int col = 0;
        hasWon = true;
        while (col < NUMBER_OF_LINES)
        {
            hasWon &= mosaic->isFilled(line, col);
        }
    }
    return hasWon;
}
