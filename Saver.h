#ifndef SAVER_H
#define SAVER_H

#include <string>
#include <iostream>
#include <istream>
#include <sstream>
#include "GameEngine.h"

using std::string;

class Saver
{
    public:
        bool save(GameEngine* gameEngine, std::string fileName);
        GameEngine* load(std::string fileName);

    private:
        bool save(GameEngine* gameEngine, std::ofstream& outputStream);
        GameEngine* load(std::istream& inputStream);
        TileType charToTileType(char c);
        Mosaic* generateMosiac(std::istream& inputStream);
        std::istringstream getLineAsStream(std::istream& inputStream);
};

#endif
