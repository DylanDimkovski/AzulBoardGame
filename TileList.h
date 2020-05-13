#ifndef TILELIST_H
#define TILELIST_H

#include "Types.h"
#include "Node.h"

class TileList
{
    public:
        TileList();
        ~TileList();
        int size();
        void clear();
        void addFront(TileType tile);
        void addBack(TileType tile);
        Node* getHead();
        TileType removeFront();
        TileType removeBack();

    private:
        Node* head;
        Node* tail;
        int length;
};

#endif