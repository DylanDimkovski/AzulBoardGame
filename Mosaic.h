#ifndef MOSIAC_H
#define MOSIAC_H

#include "Types.h"
#include "Factory.h"
#include "Line.h"
#include "TileList.h"

class Mosaic
{
public:
    Mosaic();
    ~Mosaic();
    bool isFilled(int row, int col);
    bool isFilled(int row, TileType tile);
    void setFilled(int row, int col, bool filled);
    void insertTilesIntoLine(int row, int quantity, TileType tileType);
    void addToBrokenTiles(int quantity, TileType tileType);
    Line *getLine(int line);
    bool *getWallLine(int line);
    TileList *getBrokenTiles();

private:
    Line *lines[NUMBER_OF_LINES];
    bool wall[NUMBER_OF_LINES][NUMBER_OF_LINES];
    TileList *brokenTiles;
    TileType master_wall[NUMBER_OF_LINES][NUMBER_OF_LINES] = {DARKBLUE, YELLOW, RED, BLACK, LIGTHBLUE,
                                                              LIGTHBLUE, DARKBLUE, YELLOW, RED, BLACK,
                                                              BLACK, LIGTHBLUE, DARKBLUE, YELLOW, RED,
                                                              RED, BLACK, LIGTHBLUE, DARKBLUE, YELLOW,
                                                              YELLOW, RED, BLACK, LIGTHBLUE, DARKBLUE};
};

#endif
