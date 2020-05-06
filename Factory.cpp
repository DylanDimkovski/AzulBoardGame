#include "Factory.h"

Factory::Factory(TileType arr[FACTORY_SIZE])
{
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        tiles[i] = arr[i];
    }
}

void Factory::fill(TileType arr[FACTORY_SIZE])
{
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        tiles[i] = arr[i];
    }
}

TileType *Factory::empty()
{
    TileType array[4];
    TileType *arrPtr = array;
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        if (tiles[i] != NOTILE)
        {
            array[i] = tiles[i];
            tiles[i] = NOTILE;
        }
    }
    return arrPtr;
}

int Factory::draw(TileType tileType)
{
    int count = 0;
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        if (tiles[i] == tileType)
        {
            count++;
            tiles[i] = NOTILE;
        }
    }
    return count;
}

string Factory::toString()
{
    string tiles = "";
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        if (tiles[i != NOTILE])
        {
            tiles += tiles[i] + " ";
        }
    }
    return tiles;
}