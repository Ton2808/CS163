#ifndef Khoi_h
#define Khoi_h
#include "library.h"
struct TrieNode
{
    TrieNode **children;
    bool isEndNode;
    vector<pair<string, int> > links;
    TrieNode()
    {
        children = new TrieNode *[256];
        for (int i = 0; i < 256; ++i)
            children[i] = NULL;
        isEndNode = false;
    }
};
#endif