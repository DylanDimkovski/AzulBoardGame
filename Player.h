#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "Mosaic.h"

class Player
{
public:
    Player(std::string name);
    Player(std::string name, int score, Mosaic *mosaic);
    ~Player();
    std::string getName();
    int getScore();
    std::vector<TileType> calcScore();
    Mosaic *getMosaic();
    bool hasWon();
    bool hasFirstPlayer();

private:
    int
    scoreLine(int lineNum);
    int calcRow(int index, int line);
    int calcCol(int index, int line);
    std::string name;
    int score;
    Mosaic *mosaic;
    TileType master_wall[NUMBER_OF_LINES][NUMBER_OF_LINES] = {DARKBLUE, YELLOW, RED, BLACK, LIGTHBLUE,
                                                              LIGTHBLUE, DARKBLUE, YELLOW, RED, BLACK,
                                                              BLACK, LIGTHBLUE, DARKBLUE, YELLOW, RED,
                                                              RED, BLACK, LIGTHBLUE, DARKBLUE, YELLOW,
                                                              YELLOW, RED, BLACK, LIGTHBLUE, DARKBLUE};
};

#endif // !PLAYER_H
