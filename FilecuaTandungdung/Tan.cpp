#include "Khoi.h"
#include "library.h"

vector<string> splitAndOperator(string inputString)
{
    vector<string> res;
    string temp;
    for (int i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == ' ')
        {
            res.push_back(temp);
            temp.clear();
        }
        else if (inputString[i] == 'a' && inputString[i + 1] == 'n' && inputString[i + 2] == 'd')
            i += 3;
        else
        {
            temp += inputString[i];
            if (i == inputString.length() - 1)
                res.push_back(temp);
        }
    }
    return res;
}

void ranking_AndOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
{
    vector<pair<string, int> > *tmp;
    tmp = new vector<pair<string, int> >[word.size()];
    for (int i = 0; i < word.size(); ++i)
    {
        searchInTrieNode(root, word[i], tmp[i]);
    }

    map<string, int> checkAllWordIsInFile;
    map<string, int> fwd;
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

void activateAndOperator(TrieNode *root, string inputString, int numberOfFiles)
{
    vector<string> listWords = splitAndOperator(inputString);
    vector<string> _5thLinks;
    ranking_AndOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

vector<string> splitNormalOperator(string inputString)
{
    vector<string> res;
    string temp;
    for (int i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == ' ')
        {
            res.push_back(temp);
            temp.clear();
        }
        else
        {
            temp += inputString[i];
            if (i == inputString.length() - 1)
                res.push_back(temp);
        }
    }
    return res;
}

void ranking_NormalOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
{
    vector<pair<string, int> > *tmp;
    tmp = new vector<pair<string, int> >[word.size()];
    for (int i = 0; i < word.size(); ++i)
    {
        searchInTrieNode(root, word[i], tmp[i]);
    }

    map<string, int> checkAllWordIsInFile;
    map<string, int> fwd;
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
        if (i->second >= 1)
            store.push_back(i->first);
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

void activateNormalOperator(TrieNode *root, string inputString, int numberOfFiles)
{
    vector<string> listWords = splitNormalOperator(inputString);
    vector<string> _5thLinks;
    ranking_NormalOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

vector<string> splitPriceOperator(string inputString)
{
    vector<string> res;
    string temp;
    for (int i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == ' ')
        {
            cout << temp << endl;
            res.push_back(temp);
            temp.clear();
        }
        else
        {
            temp += inputString[i];
            if (i == inputString.length() - 1)
            {
                cout << temp << endl;
                res.push_back(temp);
            }
        }
    }
    return res;
}

void ranking_PriceOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
{
    vector<pair<string, int> > *tmp;
    tmp = new vector<pair<string, int> >[word.size()];
    for (int i = 0; i < word.size(); ++i)
    {
        searchInTrieNode(root, word[i], tmp[i]);
    }

    map<string, int> checkAllWordIsInFile;
    map<string, int> fwd;
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

void activatePriceOperator(TrieNode *root, string inputString, int numberOfFiles)
{
    vector<string> listWords = splitPriceOperator(inputString);
    vector<string> _5thLinks;
    ranking_PriceOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

