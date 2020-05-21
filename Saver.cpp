#include "Saver.h"

// need to put this in gameEngine
TileType Master_Wall[5][5]{DARKBLUE, YELLOW, RED, BLACK, LIGTHBLUE,
                           LIGTHBLUE, DARKBLUE, YELLOW, RED, BLACK,
                           BLACK, LIGTHBLUE, DARKBLUE, YELLOW, RED,
                           RED, BLACK, LIGTHBLUE, DARKBLUE, YELLOW,
                           YELLOW, RED, BLACK, LIGTHBLUE, DARKBLUE};


void Saver::save(GameEngine* gameEngine, std::string fileName)
{
    std::ofstream outputStream(fileName);
    return save(gameEngine, outputStream);
}

void Saver::save(GameEngine* gameEngine, std::ofstream& outputStream)
{
    outputStream << (gameEngine->getPlayer(0) == gameEngine->getPlayerTurnID() ? "true" : "false") << std::endl;
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
        outputStream << gameEngine->getFactory(i)->toStringNoSpace() << std::endl;
    }

    // Player 1 mosiac
    Mosaic* player1Mosaic = gameEngine->getPlayer(0)->getMosaic();
    for (int i = 0; i < NUMBER_OF_LINES; ++i)
    {
        outputStream << player1Mosaic->getLine(i)->toString() << std::endl;
    }

    outputStream << player1Mosaic->getBrokenTiles()->toString() << std::endl;

    // Need to output Player 1 wall
    outputWall(outputStream, player1Mosaic);


    // Player 2 mosiac
    Mosaic* player2Mosaic = gameEngine->getPlayer(1)->getMosaic();
    for (int i = 0; i < NUMBER_OF_LINES; ++i)
    {
        outputStream << player2Mosaic->getLine(i)->toString() << std::endl;
    }

    outputStream << player2Mosaic->getBrokenTiles()->toString() << std::endl;

    // Need to output Player 2 wall
    outputWall(outputStream, player2Mosaic);


    outputStream << gameEngine->getLid()->toString() << std::endl;
    outputStream << gameEngine->getBag()->toString() << std::endl;
    outputStream.close();
}

GameEngine* Saver::load(std::string fileName, Menu* menu)
{
    GameEngine* gameEngine = nullptr;
    std::ifstream inputStream(fileName);
    if (inputStream.good())
        gameEngine = load(inputStream, menu);
    return gameEngine;
}


GameEngine* Saver::load(std::istream& inputStream, Menu* menu)
{
    GameEngine* gameEngine = new GameEngine(menu);
    int currentLine = 0;
    std::string lines[SAVE_FILE_LINES_LENGTH];
    while (inputStream.good() && currentLine < SAVE_FILE_LINES_LENGTH)
    {
        std::getline(inputStream, lines[currentLine++]);
    }

    if (currentLine != SAVE_FILE_LINES_LENGTH){
        delete gameEngine;
        throw "Incorrect number of lines, missing info";
    }

    char c = '\0';

    // Check if it's player 1's turn
    bool player1Turn = true;
    std::istringstream player1TurnStream(lines[0]);
    if (player1TurnStream.good())
    {
        std::string value;
        player1TurnStream >> value;
        player1Turn = value == "true";
    }

    // player 1
    std::string player1Name = lines[1];
    int player1Score = std::stoi(lines[2]);

    // player 2
    std::string player2Name = lines[3];
    int player2Score = std::stoi(lines[4]);

    // Create center factory
    std::vector<TileType> centerFactory;
    std::istringstream centerFactoryStream(lines[5]);
    while (centerFactoryStream.get(c))
    {
        TileType toAdd = charToTileType(c);
        if (toAdd != NOTILE)
            centerFactory.push_back(toAdd);
    }
    
    // Create all factories
    Factory* factories[NUM_FACTORIES];
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        // Create a single factory
        TileType tiles[FACTORY_SIZE] = {NOTILE, NOTILE, NOTILE, NOTILE};
        if (!lines[6 + i].empty())
        {
            std::istringstream factoryStream(lines[6 + i]);
            for (int j = 0; j < FACTORY_SIZE; ++j)
            {
                if (factoryStream.good())
                {
                    c = '\0';
                    factoryStream >> c;
                    if (selectableTile(c))
                        tiles[j] = charToTileType(c);
                    else throw "A factory contains an unselectable tile";
                }
            }
        }
        factories[i] = new Factory(tiles);
    }

    // Create player 1 mosaic
    Mosaic* player1mosaic = generateMosiac(lines, 11);

    // Create player 2 mosaic
    Mosaic* player2mosaic = generateMosiac(lines, 18);

    // Create lid
    TileList* lid = new TileList();
    std::istringstream lidStream(lines[25]);
    while (lidStream.good())
    {
        c = '\0';
        lidStream >> c;
        TileType tile = charToTileType(c);
        if (tile != NOTILE && tile != FIRSTPLAYER)
        {
            lid->addBack(tile);
        }
    }

    // Create bag
    TileList* bag = new TileList();
    std::istringstream bagStream(lines[26]);
    while (bagStream.good())
    {
        c = '\0';
        bagStream >> c;
        TileType tile = charToTileType(c);
        if (tile != NOTILE && tile != FIRSTPLAYER)
        {
            bag->addBack(tile);
        }
    }

    gameEngine->addPlayer(player1Name, player1Score, player1mosaic);
    gameEngine->addPlayer(player2Name, player2Score, player2mosaic);

    gameEngine->fillBag(bag);
    gameEngine->fillLid(lid);

    gameEngine->fillFactories(factories);

    gameEngine->fillCenterPile(centerFactory);

    if (player1Turn) gameEngine->setPlayerTurn(0);
    else gameEngine->setPlayerTurn(1);

    return gameEngine;
}

void Saver::outputWall(std::ofstream& outputStream, Mosaic* mosaic)
{
    for (int row = 0; row < NUMBER_OF_LINES; ++row)
    {
        for (int col = 0; col < NUMBER_OF_LINES; ++col)
        {
            if (mosaic->isFilled(row, col))
                outputStream << char(Master_Wall[row][col]);
            else
                outputStream << tileTypeToLower(Master_Wall[row][col]);
        }
    }
    outputStream << std::endl;
}

Mosaic* Saver::generateMosiac(std::string lines[28], int startingLine)
{
    Mosaic* mosaic = new Mosaic();
    for (int i = 0; i < NUMBER_OF_LINES; ++i)
    {   
        std::istringstream lineStream(lines[startingLine + i]);
        char c;
        for (int j = 0; j < i+1; ++j)
        {
            lineStream >> c;
            TileType toAdd = charToTileType(c);
            if (toAdd != NOTILE && toAdd != FIRSTPLAYER)
            {
                mosaic->insertTilesIntoLine(i, 1, toAdd);
            }
        }
    }
    
    std::istringstream brokenTilesStream(lines[startingLine + 5]);
    char c;
    while (brokenTilesStream.get(c))
    {
        mosaic->addToBrokenTiles(1, charToTileType(c));
    }
    
    std::istringstream wallStream(lines[startingLine + 6]);
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

char Saver::tileTypeToLower(TileType tileType)
{
    char result = '\0';
    if (tileType == RED) result = 'r';
    else if (tileType == YELLOW) result = 'y';
    else if (tileType == DARKBLUE) result = 'b';
    else if (tileType == LIGTHBLUE) result = 'l';
    else if (tileType == BLACK) result = 'u';
    else result = char(tileType);
    return result;
}
