#ifndef TILELIST_H
#define TILELIST_H

#include "Types.h"
#include "Node.h"
#include <string>

class TileList
{
    public:
        TileList();
        ~TileList();
        int size();
        void clear();
        void addFront(TileType tile);
        void addBack(TileType tile);
        TileType removeFront();
        TileType removeBack();
        std::string toString();

    private:
        Node* head;
        Node* tail;
        int length;
};

#endif