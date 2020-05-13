#include "Utils.h"

TileType charToTileType(char c)
{
    TileType result = NOTILE;
    if (c == 'R') result = RED;
    else if (c == 'Y') result = YELLOW;
    else if (c == 'B') result = DARKBLUE;
    else if (c == 'L') result = LIGTHBLUE;
    else if (c == 'U') result = BLACK;
    else if (c == 'F') result = FIRSTPLAYER;
    else if (c == '.') result = NOTILE;
    return result;
}
