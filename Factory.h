#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include "Types.h"

using std::string;

class Factory
{
public:
    Factory();
    Factory(TileType array[FACTORY_SIZE]);
    void fill(TileType array[FACTORY_SIZE]);
    TileType *empty();
    int draw(TileType tileType);
    string toString();

private:
    TileType tiles[FACTORY_SIZE];
};

#endif // !FACTORY_H