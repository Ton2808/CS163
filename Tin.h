#ifndef Tin_h
#define Tin_h

#include "Khoi.h"

// Function
// 3
bool checkMinusOperator (string inputString);
void activateMinusOperator(TrieNode *root, string inputString, int numberOfFiles);
void rankingMinusOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles);

// 8
bool checkHashtagsOperator (string inputString);
void activateHashtagsOperator(TrieNode *root, string inputString, int numberOfFiles);
void rankingHashtagsOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles);

// 11
bool checkRangeOperator (string inputString);
void activateRangeOperator(TrieNode *root, string inputString, int numberOfFiles);
void rankingRangeOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles);

// Support
vector<string> splitOperator(string inputString, char oper);
vector<string> find_5thLinks (map<string, int> fwd, vector<string> store, int numberOfFiles);

#endif
