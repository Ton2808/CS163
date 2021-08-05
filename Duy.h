#ifndef Duy_h
#define Duy_h
#include "library.h"
using namespace std;
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

//Task 2: OR operation
bool checkOROperator(string inputString);

#endif