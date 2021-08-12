#ifndef Duy_h
#define Duy_h
#include "Khoi.h"
#include "library.h"
using namespace std;
// struct TrieNode
// {
//     TrieNode **children;
//     bool isEndNode;
//     vector<pair<string, int> > links;
//     TrieNode()
//     {
//         children = new TrieNode *[256];
//         for (int i = 0; i < 256; ++i)
//             children[i] = NULL;
//         isEndNode = false;
//     }
// };

//Duy Task
//Task 2
bool checkOROperator(string inputString);
vector<string> splitOROperator(string inputString);
void ranking_OROperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles);
void activateOROperator(TrieNode *root, string inputString, int numberOfFiles);
//Task 4: intitle:a b
//in title have a and b
//before intitle is in every where
void getTitleToFile(string fileName, TrieNode *&root, ifstream &fin);
bool checkIntitleOperator(string inputString);
vector<string> splitIntitleOperator(string inputString);
void activateIntitleOperator(TrieNode *root, string inputString, int numberOfFiles);
//Task 12: synonym
bool checkSynonymOperator(string inputString);
vector<string> getSynonymFromFile(string inputString, ifstream &fin);
void activateSynonymOperator(TrieNode *root, string inputString, int numberOfFiles, ifstream &fin);

#endif