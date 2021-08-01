#ifndef Khoi_h
#define Khoi_h
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

void insertWordToTrie(TrieNode *&root, string a, string link);
bool searchInTrieNode(TrieNode *root, string a, vector<pair<string, int> > &getLinks);
void setUpData(string dataFileName, ifstream &fin, string *&fileName, int &numberFiles);
void getStringsStopWord(string fileStopWord, string *&stopWord, ifstream &fin);
bool isStopWord(string stopWord[], string word, int number);
bool checkANDOperator(string inputString);
bool checkOROperator(string inputString);
vector<int> checkOption(string inputString);
void getFilesToTrie(string fileName, ifstream &fin, TrieNode *&root, string stopWord[]);
#endif