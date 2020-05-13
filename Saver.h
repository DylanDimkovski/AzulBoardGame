#ifndef SAVER_H
#define SAVER_H

#include <string>
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include "GameEngine.h"
#include "Menu.h"
#include "Factory.h"

using std::string;

class Saver
{
    public:
        bool save(GameEngine* gameEngine, std::string fileName);
        GameEngine* load(std::string fileName);

    private:
        bool save(GameEngine* gameEngine, std::ofstream& outputStream);
        GameEngine* load(std::istream& inputStream);
        void outputWall(std::ofstream& outputStream, Mosaic* mosaic);
        char tileTypeToLower(TileType tileType);
        Mosaic* generateMosiac(std::istream& inputStream);
        std::istringstream getLineAsStream(std::istream& inputStream);
};

#endif
