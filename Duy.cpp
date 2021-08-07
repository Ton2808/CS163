#include "Duy.h"
#include "Khoi.h"
#include "library.h"
using namespace std;

//Task 2 + 4 + 12

//Task 2: OR operator
bool checkOROperator(string inputString)
{
    regex operator_AND("[a-z]*[A-Z]*[0-9]*(\\s+)OR(\\s+)([a-z]*[A-Z]*[0-9]*)+");
    if (regex_match(inputString.begin(), inputString.end(), operator_AND))
        return true;
    return false;
}

vector<string> splitOROperator(string inputString)
{
    vector<string> res;
    string temp;
    for (int i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == ' ')
            continue;
        if (inputString[i] == 'OR')
        {
            res.push_back(temp);
            temp.clear();
        }
        else
        {
            temp += inputString[i];
            if (i == inputString.length() - 1)
            {
                res.push_back(temp);
            }
        }
    }
    return res;
}

void ranking_OROperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
{
    vector<pair<string, int> > *tmp;
    tmp = new vector<pair<string, int> >[word.size()];
    for (int i = 0; i < word.size(); ++i)
    {
        searchInTrieNode(root, word[i], tmp[i]);
    }

    //Check if there are no document contain a or b then return 
    bool check=false;
    for (int i=0; i < word.size(); i++){
        if (!tmp[i].empty()){
            check=true;
            break;
        }
    }
    if (check==false) return;
    //Calculate w for each document contained a, b and store link to string store
    set<string> store;
    map<string,float> w;
    for (int i=0; i < word.size(); i++){
        for (int j=0; j < tmp[i].size(); j++){
            //if link has both a and b then we sum their w.
            w[tmp[i][j].first] += tmp[i][j].second * log((float)numberOfFiles / tmp[i].size());
            store.insert(tmp[i][j].first);
        }
    }
    //Take 5th largest in w
    
    for (int i=0; i < 5; i++){
        int max=-1;
        set<string>::iterator itr, index;
        for (itr=store.begin(); itr != store.end(); itr++){
            if (w[*itr] > max){
                max = w[*itr];
                index = itr;
            }
        }
        _5thLinks.push_back(*index);
        store.erase(*index); 
    }
}

void activateOROperator(TrieNode *root, string inputString, int numberOfFiles)
{
    vector<string> listWords = splitOROperator(inputString);
    vector<string> _5thLinks;
    ranking_OROperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

//Task 4: intitle:a b
//in title have a and b
//before intitle is in every where

