#include<bits/stdc++.h>
using namespace std;

struct Trie{
    int cnt;
    vector < int > pos;
    Trie *child[257];
    Trie()
    {
        cnt = 0;
        pos.clear();
        for(int i = 0 ; i <= 256 ; i++)
            child[i] = NULL;
    }
};

#ifndef Myfunction_h
#define Myfunction_h



#endif // Myfunction_h
