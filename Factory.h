#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <vector>
#include "Types.h"

using std::string;

class Factory
{
public:
    Factory();
    Factory(TileType array[FACTORY_SIZE]);
    void fill(TileType array[FACTORY_SIZE]);
    std::vector<TileType> empty();
    int draw(TileType tileType);
    string toString();
    bool isEmpty();

private:
    TileType tiles[FACTORY_SIZE];
    bool clear;
};

#endif // !FACTORY_H