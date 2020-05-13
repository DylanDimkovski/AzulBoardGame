#ifndef TYPES_H
#define TYPES_H

#define NUMBER_OF_LINES 5
#define BROKEN_TILES_LENGTH 7
#define NUMBER_OF_PLAYERS 2
#define NUMBER_OF_COLOURS 5
#define NUMBER_OF_EACH_COLOUR 20
#define FACTORY_SIZE 4
#define NUM_FACTORIES 5

enum TileType
{
    RED = 'R',
    YELLOW = 'Y',
    DARKBLUE = 'B',
    LIGTHBLUE = 'L',
    BLACK = 'U',
    FIRSTPLAYER = 'F',
    NOTILE = '.'
};

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

TileType Master_Wall[5][5]{DARKBLUE, YELLOW, RED, BLACK, LIGTHBLUE,
                           LIGTHBLUE, DARKBLUE, YELLOW, RED, BLACK,
                           BLACK, LIGTHBLUE, DARKBLUE, YELLOW, RED,
                           RED, BLACK, LIGTHBLUE, DARKBLUE, YELLOW,
                           YELLOW, RED, BLACK, LIGTHBLUE, DARKBLUE};

#endif