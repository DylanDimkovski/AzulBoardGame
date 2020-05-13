#include "Mosaic.h"

Mosaic::Mosaic()
{
    for (int i = 0; i < NUMBER_OF_LINES; ++i)
    {
        lines[i] = new Line(i + 1);
    }

    for (int i = 0; i < NUMBER_OF_LINES; ++i)
    {
        for (int j = 0; j < NUMBER_OF_LINES; ++j)
        {
            wall[i][j] = false;
        }
    }
}

Mosaic::~Mosaic()
{
    for (int i = 0; i < NUMBER_OF_LINES; ++i)
    {
        delete lines[i];
    }
}

bool Mosaic::isFilled(int row, int col)
{
    return wall[row][col];
}

void Mosaic::setFilled(int row, int col, bool filled)
{
    wall[row][col] = filled;
}

void Mosaic::insertTilesIntoLine(int row, int quantity, TileType tileType)
{
    int overflow = lines[row]->addTiles(quantity, tileType);
    for (int i = 0; i < overflow; ++i)
    {
        brokenTiles.addBack(tileType);
    }
}

Line *Mosaic::getLine(int line)
{
    return lines[line];
}
