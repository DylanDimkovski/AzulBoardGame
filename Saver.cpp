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

    if (currentLine != SAVE_FILE_LINES_LENGTH)
    {
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
        if (value != "true" && value != "false")
        {
            delete gameEngine;
            throw "Player 1 turn value is invalid";
        }
        player1Turn = value == "true";
    }

    // player 1
    if (isWhiteSpace(lines[1]))
    {
        delete gameEngine;
        throw "Player 1 name cannot be empty";
    }
    std::string player1Name = lines[1];
    int player1Score;
    try
    {
        player1Score = std::stoi(lines[2]);
    }
    catch (...)
    {
        delete gameEngine;
        throw "Player 1 score is not valid";
    }

    // player 2
    if (isWhiteSpace(lines[3]))
    {
        delete gameEngine;
        throw "Player 2 name cannot be empty";
    }
    std::string player2Name = lines[3];
    int player2Score;
    try
    {
        player2Score = std::stoi(lines[4]);
    }
    catch (...)
    {
        delete gameEngine;
        throw "Player 2 score is not valid";
    }

    // Create center factory
    bool addedFirstTile = false;
    std::vector<TileType> centerFactory;
    std::istringstream centerFactoryStream(lines[5]);
    while (centerFactoryStream.get(c))
    {
        if (selectableTile(c) || (c == FIRSTPLAYER && !addedFirstTile))
        {
            addedFirstTile |= c == FIRSTPLAYER;
            centerFactory.push_back(charToTileType(c));
        }
        else
        {
            delete gameEngine;
            throw "Problem reading center factory";
        }
    }
    gameEngine->fillCenterPile(centerFactory);
    
    // Create all factories
    Factory* factories[NUM_FACTORIES] = {nullptr};
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        // Create a single factory
        TileType tiles[FACTORY_SIZE] = {NOTILE, NOTILE, NOTILE, NOTILE};
        if (!lines[6 + i].empty())
        {
            std::istringstream factoryStream(lines[6 + i]);
            for (int j = 0; j < FACTORY_SIZE; ++j)
            {
                if (factoryStream.get(c))
                {
                    if (c != NOTILE && !selectableTile(c))
                    {
                        delete gameEngine;
                        cleanUpFactories(factories);
                        throw "A factory contains an invalid tile";
                    }
                    tiles[j] = charToTileType(c);
                }
                else
                {
                    delete gameEngine;
                    cleanUpFactories(factories);
                    throw "A factory is missing some tiles";
                }
            }
        }

        if (isValidFactory(tiles))
            factories[i] = new Factory(tiles);
        else
        {
            delete gameEngine;
            cleanUpFactories(factories);
            throw "A factory is invalid";
        }
    }
    gameEngine->fillFactories(factories);

    // Create player 1 mosaic
    Mosaic* player1mosaic = nullptr;
    try
    {
        player1mosaic = generateMosiac(lines, 11);
    }
    catch (const char* errorMessage)
    {
        delete gameEngine;
        throw errorMessage;
    }
    gameEngine->addPlayer(player1Name, player1Score, player1mosaic);

    // Create player 2 mosaic
    Mosaic* player2mosaic = nullptr;
    try
    {
        player2mosaic = generateMosiac(lines, 18);
    }
    catch (const char* errorMessage)
    {
        delete gameEngine;
        throw errorMessage;
    }
    gameEngine->addPlayer(player2Name, player2Score, player2mosaic);


    // Create lid
    TileList* lid = new TileList();
    std::istringstream lidStream(lines[25]);
    while (lidStream.get(c))
    {
        if (!selectableTile(c))
        {
            delete gameEngine;
            delete lid;
            throw "The lid contains an unselectable tile";
        }
        lid->addBack(charToTileType(c));
    }
    gameEngine->fillLid(lid);

    // Create bag
    TileList* bag = new TileList();
    std::istringstream bagStream(lines[26]);
    while (bagStream.get(c))
    {
        if (!selectableTile(c))
        {
            delete gameEngine;
            delete bag;
            throw "The bag contains an unselectable tile";
        }
        bag->addBack(charToTileType(c));
    }
    gameEngine->fillBag(bag);

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

Mosaic* Saver::generateMosiac(std::string lines[SAVE_FILE_LINES_LENGTH], int startingLine)
{
    Mosaic* mosaic = new Mosaic();
    std::istringstream wallStream(lines[startingLine + 6]);
    for (int row = 0; row < NUMBER_OF_LINES; ++row)
    {
        for (int col = 0; col < NUMBER_OF_LINES; ++col)
        {
            char c = '\0';
            if (wallStream.get(c))
            {
                if (selectableTile(std::toupper(c)))
                    mosaic->setFilled(row, col, std::isupper(c));
                else
                {
                    delete mosaic;
                    throw "A mosaic wall contains an invalid tile";
                }
            }
            else
            {
                delete mosaic;
                throw "A mosaic wall is missing tiles";
            }
        }
    }

    for (int i = 0; i < NUMBER_OF_LINES; ++i)
    {   
        std::istringstream lineStream(lines[startingLine + i]);
        char c = '\0';
        for (int j = 0; j < i+1; ++j)
        {
            lineStream >> c;
            TileType toAdd = charToTileType(c);
            if (c == NOTILE || (selectableTile(c) && mosaic->getLine(i)->canAddTiles(toAdd) && !mosaic->isFilled(i, toAdd)))
                mosaic->insertTilesIntoLine(i, 1, toAdd);
            else
            {
                delete mosaic;
                throw "A mosaic contains an invalid line";
            }
        }
    }
    
    std::istringstream brokenTilesStream(lines[startingLine + 5]);
    char c = '\0';
    bool addedFirstTile = false;
    while (brokenTilesStream.get(c))
    {
        if (selectableTile(c) || (c == FIRSTPLAYER && !addedFirstTile))
        {
            addedFirstTile |= c == FIRSTPLAYER;
            mosaic->addToBrokenTiles(1, charToTileType(c));
        }
        else
        {
            delete mosaic;
            throw "There is a problem in the broken tiles";
        }
    }

    return mosaic;
}

void Saver::cleanUpFactories(Factory* factories[])
{
    for (int i = 0; i < NUM_FACTORIES; ++i)
        if (factories[i] != nullptr) delete factories[i];
}

bool Saver::isValidFactory(TileType tiles[])
{
    bool allNotile = true;
    bool allSelectable = true;
    for (int i = 0; i < FACTORY_SIZE; ++i)
    {
        allNotile &= tiles[i] == NOTILE;
        allSelectable &= selectableTile(tiles[i]);
    }
    return allNotile || allSelectable;
}
