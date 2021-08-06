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

//setup data
void setUpData(string dataFileName, ifstream &fin, string *&fileName, int &numberFiles);
void insertWordToTrie(TrieNode *&root, string a, string link);
bool searchInTrieNode(TrieNode *root, string a, vector<pair<string, int> > &getLinks);
void getFilesToTrie(string fileName, ifstream &fin, TrieNode *&root, string stopWord[]);
void reConstructInput(string &word);

//stop word
bool isStopWord(string stopWord[], string word, int number);
void getStringsStopWord(string fileStopWord, string *&stopWord, ifstream &fin);

//check opertor
bool checkANDOperator(string inputString);
bool checkOROperator(string inputString);
bool checkPlusOpertor(string inputString);
bool checkExactlyOperator(string inputString);

//operator plus
vector<string> splitPlusOperator(string inputString);
void activatePlusOperator(TrieNode *root, string inputString, int numberOfFiles);

//operator exacly
vector<string> splitWordInSpace(string inputString);
void acitvateExactlyOperator(TrieNode *root, string inputString, int numberOFiles);
void ranking_ExactlyOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles);

//ranking
void ranking_PlusOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles);

//print
void print(vector<string> keyWords, vector<string> _5thFiles);
void printOneFile(string fileName, ifstream &fin, vector<string> keyWords);
bool isHighLight(string word, vector<string> keyWord);

//search
void checkOption(TrieNode *root, string inputString, int numberOfFiles);
#endif