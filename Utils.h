#ifndef UTILS_H
#define UTILS_H

#include "Types.h"

TileType charToTileType(char c);
bool selectableTile(char c);
bool selectableTile(TileType tile);
bool validTile(char c);
char tileTypeToLower(TileType tileType);


#endif