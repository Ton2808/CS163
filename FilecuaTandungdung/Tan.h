#ifndef Tan_h
#define Tan_h
#include "library.h"
using namespace std;

//Normal operator
vector<string> splitNormalOperator(string inputString);
void activateNormalOperator(TrieNode *root, string inputString, int numberOfFiles);

//operator AND
vector<string> splitWordInAND(string inputString);
void activateAndOperator(TrieNode *root, string inputString, int numberOFiles);

//operator $
vector<string> splitWordInPrice(string inputString);
void activatePriceOperator(TrieNode *root, string inputString, int numberOFiles);

#endif
