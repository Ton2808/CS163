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

vector<string> splitOROperator(TrieNode *root, string inputString)
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

void ranking_PlusOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
{
    vector<pair<string, int> > *tmp;
    tmp = new vector<pair<string, int> >[word.size()];
    for (int i = 0; i < word.size(); ++i)
    {
        searchInTrieNode(root, word[i], tmp[i]);
    }

    map<string, int> checkAllWordIsInFile;
    map<string, int> fwd;
    //check how many word in file contained
    for (int i = 0; i < word.size(); ++i)
    {
        for (int j = 0; j < tmp[i].size(); ++j)
        {
            if (fwd[tmp[i][j].first] < tmp[i][j].second)
            {
                fwd[tmp[i][j].first] = tmp[i][j].second;
            }
            checkAllWordIsInFile[tmp[i][j].first]++;
        }
    }
    vector<string> store;
    for (map<string, int>::iterator i = checkAllWordIsInFile.begin(); i != checkAllWordIsInFile.end(); ++i)
    {
        if (i->second == word.size())
        {
            store.push_back(i->first);
        }
    }
    int fwD = store.size();
    if (fwD)
    {
        map<string, float> w;
        for (int i = 0; i < store.size(); ++i)
        {
            w[store[i]] = fwd[store[i]] * log((float)numberOfFiles / fwD);
        }
        bool *isLooped = new bool[store.size()];
        for (int i = 0; i < store.size(); ++i)
            isLooped[i] = false;
        for (int i = 0; i < 5; ++i)
        {
            int max = -1;
            int index = -1;
            for (int j = 0; j < store.size(); ++j)
            {
                if (!isLooped[j])
                {
                    if (w[store[j]] > max)
                    {
                        index = j;
                        max = w[store[j]];
                    }
                }
            }
            if (index != -1)
            {
                isLooped[index] = true;
                _5thLinks.push_back(store[index]);
            }
        }
    }
}

