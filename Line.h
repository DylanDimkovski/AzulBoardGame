#ifndef LINE_H
#define LINE_H

#include "TileList.h"
#include "Types.h"

class Line
{
    public:
        Line(int maxSize);
        Line(int maxSize, int numTiles, TileType tileType);
        int addTiles(int quantity, TileType tileType);
        void removeTiles();
        TileType getTileType();
        bool hasTileType();
        int getNumTiles();
        int getMaxSize();

    private:
        int maxSize;
        int numTiles;
        TileType tileType;
};


#endif