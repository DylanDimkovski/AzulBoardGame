#ifndef LINE_H
#define LINE_H

#include "TileList.h"
#include "Types.h"
#include <string>

class Line
{
public:
    Line(int maxSize);
    Line(int maxSize, int numTiles, TileType tileType);
    int addTiles(int quantity, TileType tileType);
    void removeTiles();
    TileType getTileType();
    int getNumTiles();
    int getMaxSize();
    std::string toString();
    bool canAddTiles(TileType tileType);

private:
    int maxSize;
    int numTiles;
    TileType tileType;
};

#endif