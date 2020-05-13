#include "Saver.h"

bool Saver::save(GameEngine* gameEngine, std::string fileName)
{
    std::ofstream outputStream(fileName);
    return save(gameEngine, outputStream);
}

bool Saver::save(GameEngine* gameEngine, std::ofstream& outputStream)
{
    outputStream << gameEngine->getRandomSeed() << std::endl;
    outputStream << (gameEngine->isPlayer1Turn() ? "true" : "false") << std::endl;
    // Player 1 index
    outputStream << gameEngine->getPlayer(0)->getName() << std::endl;
    outputStream << gameEngine->getPlayer(0)->getScore() << std::endl;

    // Player 2 index
    outputStream << gameEngine->getPlayer(1)->getName() << std::endl;
    outputStream << gameEngine->getPlayer(1)->getScore() << std::endl;

    std::vector<TileType> centerPile = gameEngine->getCenterPile();
    for (unsigned int i = 0; i < centerPile.size(); ++i)
    {
        outputStream << char(centerPile.at(i));
    }
    outputStream << std::endl;

    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        outputStream << gameEngine->getFactory(i)->toString() << std::endl;
    }

    // Player 1 mosiac
    Mosaic* player1Mosaic = gameEngine->getPlayer(0)->getMosaic();
    for (int i = 0; i < NUMBER_OF_LINES; ++i)
    {
        outputStream << player1Mosaic->getLine(i)->toString() << std::endl;
    }

    outputStream << player1Mosaic->getBrokenTiles().toString() << std::endl;

    // Need to output Player 1 wall
    outputWall(outputStream, player1Mosaic);


    // Player 2 mosiac
    Mosaic* player2Mosaic = gameEngine->getPlayer(1)->getMosaic();
    for (int i = 1; i <= NUMBER_OF_LINES; ++i)
    {
        outputStream << player2Mosaic->getLine(i)->toString() << std::endl;
    }

    outputStream << player2Mosaic->getBrokenTiles().toString() << std::endl;

    // Need to output Player 2 wall
    outputWall(outputStream, player2Mosaic);


    outputStream << gameEngine->getLid().toString() << std::endl;
    outputStream << gameEngine->getBag().toString() << std::endl;
    outputStream.close();
}

GameEngine* Saver::load(std::string fileName)
{
    std::ifstream inputStream(fileName);
    return load(inputStream);
}


GameEngine* Saver::load(std::istream& inputStream)
{
    GameEngine* gameEngine = new GameEngine(new Menu());
    // int currentLine = 0;
    // std::string lines[28];
    // while (inputStream.good() && currentLine < 28)
    // {
    //     std::getline(inputStream, lines[currentLine++]);
    // }


    // Get seed
    int seed;
    std::istringstream seedStream = getLineAsStream(inputStream);
    if (seedStream.good()) seedStream >> seed;

    // Check if it's player 1's turn
    bool player1Turn;
    std::istringstream player1TurnStream = getLineAsStream(inputStream);
    if (player1TurnStream.good())
    {
        std::string value;
        player1TurnStream >> value;
        player1Turn = value == "true";
    }

    // player 1
    std::string player1Name;
    int player1Score;
    // Get player 1 name
    std::getline(inputStream, player1Name);
    // Get player 1 score
    inputStream >> player1Score;

    // player 2
    std::string player2Name;
    int player2Score;
    // Get player 2 name
    std::getline(inputStream, player2Name);
    // Get player 2 score
    inputStream >> player2Score;

    // Create center factory
    std::vector<TileType> centerFactory;
    std::istringstream centerFactoryStream = getLineAsStream(inputStream);
    while (centerFactoryStream.good())
    {
        char c;
        centerFactoryStream >> c;
        centerFactory.push_back(charToTileType(c));
    }
    
    // Create all factories
    Factory* factories[NUM_FACTORIES];
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        // Create a single factory
        TileType tiles[FACTORY_SIZE];
        std::istringstream factoryStream = getLineAsStream(inputStream);
        for (int j = 0; j < FACTORY_SIZE; ++j)
        {
            if (factoryStream.good())
            {
                char c;
                factoryStream >> c;
                tiles[j] = charToTileType(c);
            }
        }
        factories[i]->fill(tiles);
    }

    // Create player 1 mosaic
    Mosaic* player1mosaic = generateMosiac(inputStream);

    // Create player 2 mosaic
    Mosaic* player2mosaic = generateMosiac(inputStream);

    // Create lid
    TileList lid;
    std::istringstream lidStream = getLineAsStream(inputStream);
    while (lidStream.good())
    {
        char c;
        lidStream >> c;
        TileType tile = charToTileType(c);
        if (tile != NOTILE && tile != FIRSTPLAYER)
        {
            lid.addBack(tile);
        }
    }

    // Create bag
    TileList bag;
    std::istringstream bagStream = getLineAsStream(inputStream);
    while (bagStream.good())
    {
        char c;
        bagStream >> c;
        TileType tile = charToTileType(c);
        if (tile != NOTILE && tile != FIRSTPLAYER)
        {
            bag.addBack(tile);
        }
    }

    gameEngine->addPlayer(player1Name, player1Score, player1mosaic);
    gameEngine->addPlayer(player2Name, player2Score, player2mosaic);

    gameEngine->fillBag(bag);
    gameEngine->fillLid(lid);

    gameEngine->fillFactories(factories);

    if (player1Turn) gameEngine->setPlayerTurn(0);
    else gameEngine->setPlayerTurn(1);

    return gameEngine;
}

void Saver::outputWall(std::ofstream& outputStream, Mosaic* mosaic)
{
    for (int row = 0; NUMBER_OF_LINES; ++row)
    {
        for (int col = 0; NUMBER_OF_LINES; ++col)
        {
            if (mosaic->isFilled(row, col))
                outputStream << char(Master_Wall[row][col]);
            else
                outputStream << tileTypeToLower(Master_Wall[row][col]);
        }
    }
    outputStream << std::endl;
}

Mosaic* Saver::generateMosiac(std::istream& inputStream)
{
    Mosaic* mosaic = new Mosaic();
    char c;
    for (int i = 1; i <= NUMBER_OF_LINES; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            inputStream >> c;
            TileType toAdd = charToTileType(c);
            if (toAdd != NOTILE && toAdd != FIRSTPLAYER)
            {
                mosaic->insertTilesIntoLine(i, 1, toAdd);
            }
        }
    }
    
    std::istringstream brokenTilesStream = getLineAsStream(inputStream);
    while (brokenTilesStream.good())
    {
        char c;
        brokenTilesStream >> c;
        mosaic->addToBrokenTiles(1, charToTileType(c));
    }
    
    std::istringstream wallStream = getLineAsStream(inputStream);
    for (int row = 0; row < NUMBER_OF_LINES; ++row)
    {
        for (int col = 0; col < NUMBER_OF_LINES; ++col)
        {
            char c;
            wallStream >> c;
            TileType toAdd = charToTileType(c);
            if (toAdd != NOTILE && toAdd != FIRSTPLAYER)
                mosaic->setFilled(row, col, true);
        }
    }

    return mosaic;
}

std::istringstream Saver::getLineAsStream(std::istream& inputStream)
{
    std::string line;
    std::getline(inputStream, line);
    return std::istringstream(line);
}


char Saver::tileTypeToLower(TileType tileType)
{
    char result = '\0';
    if (tileType == 'R') result = 'r';
    else if (tileType == 'Y') result = 'y';
    else if (tileType == 'B') result = 'b';
    else if (tileType == 'L') result = 'l';
    else if (tileType == 'U') result = 'u';
    else result = char(tileType);
    return result;
}