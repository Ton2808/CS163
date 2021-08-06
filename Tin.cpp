#include "Tin.h"

//----------------------------------------------------------------
// Task 3

bool checkMinusOperator (string inputString) {
    regex operator_Minus("(.*)( -)(.*)");
    if (regex_match(inputString, operator_Minus))
        return true;
    return false;
}

void activateMinusOperator(TrieNode *root, string inputString, int numberOfFiles) {
    vector<string> listWords = splitOperator(inputString, '-');
    vector<string> _5thLinks;
    rankingMinusOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

void rankingMinusOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles) {
    vector<pair<string, int>> *tmp;
    tmp = new vector<pair<string, int>>[word.size()];
    // Get all the links in the trie
    for (int i = 0; i < word.size(); ++i)
        searchInTrieNode(root, word[i], tmp[i]);

    // assume that there just two word: A -B
    vector<pair<string, int>>::iterator iteratorWord1 = tmp[1].begin();
    vector<pair<string, int>>::iterator iteratorWord2 = tmp[2].begin();
    // remove link have B
    for (int i = 0; i < tmp[1].size(); ++i) {
        for (int j = 0; j < tmp[2].size(); ++j) {
            if (tmp[1][i].first == tmp[2][j].first) {
                tmp[1].erase(iteratorWord1 + i);
                tmp[2].erase(iteratorWord2 + j);
            }
        }
    }

    map<string, int> checkAllWordIsInFile;
    map<string, int> fwd;
    for (int j = 0; j < tmp[1].size(); ++j) {
        if (fwd[tmp[1][j].first] < tmp[1][j].second) {
            fwd[tmp[1][j].first] = tmp[1][j].second;
        }
        ++ checkAllWordIsInFile[tmp[1][j].first]; // cout how many file for 1 word
    }

    vector<string> store;
    for (map<string, int>::iterator i = checkAllWordIsInFile.begin(); i != checkAllWordIsInFile.end(); ++i)
        // if (i->second == word.size())
        store.push_back(i->first);

    int fwD = store.size();

    if (fwD) {
        map<string, float> w;
        for (int i = 0; i < store.size(); ++i)
            w[store[i]] = fwd[store[i]] * log((float)numberOfFiles / fwD);

        bool *isLooped = new bool[store.size()];
        for (int i = 0; i < store.size(); ++i)
            isLooped[i] = false;
        // find 5th max 
        for (int i = 0; i < 5; ++i) {
            int max = -1, index = -1;
            for (int j = 0; j < store.size(); ++j)
                if (!isLooped[j])
                    if (w[store[j]] > max) {
                        index = j;
                        max = w[store[j]];
                    }
            if (index != -1) {
                isLooped[index] = true;
                _5thLinks.push_back(store[index]);
            }
        }
    }
}
/// for reuse code
vector<string> find_5thLinks () {

}

//----------------------------------------------------------------
// Task 8
bool checkHashtagsOperator (string inputString) {
    regex operator_Hashtags("(#)(.*)");
    if (regex_match(inputString, operator_Hashtags))
        return true;
    return false;
}

void activateHashtagsOperator(TrieNode *root, string inputString, int numberOfFiles) {
    vector<string> listWords = splitOperator(inputString, '#');
    vector<string> _5thLinks;
    rankingHashtagsOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

void rankingHashtagsOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles) {
    vector<pair<string, int>> *tmp;
    tmp = new vector<pair<string, int>>[word.size()];
    // Get all the links in the trie
    for (int i = 0; i < word.size(); ++i)
        searchInTrieNode(root, word[i], tmp[i]);

    // // assume that there just two word: A -B
    // vector<pair<string, int>>::iterator iteratorWord1 = tmp[1].begin();
    // vector<pair<string, int>>::iterator iteratorWord2 = tmp[2].begin();
    // // remove link have B
    // for (int i = 0; i < tmp[1].size(); ++i) {
    //     for (int j = 0; j < tmp[2].size(); ++j) {
    //         if (tmp[1][i].first == tmp[2][j].first) {
    //             tmp[1].erase(iteratorWord1 + i);
    //             tmp[2].erase(iteratorWord2 + j);
    //         }
    //     }
    // }

    map<string, int> checkAllWordIsInFile;
    map<string, int> fwd;
    for (int j = 0; j < tmp[1].size(); ++j) {
        if (fwd[tmp[1][j].first] < tmp[1][j].second) {
            fwd[tmp[1][j].first] = tmp[1][j].second;
        }
        ++ checkAllWordIsInFile[tmp[1][j].first]; // cout how many file for 1 word
    }

    vector<string> store;
    for (map<string, int>::iterator i = checkAllWordIsInFile.begin(); i != checkAllWordIsInFile.end(); ++i)
        // if (i->second == word.size())
        store.push_back(i->first);

    int fwD = store.size();

    if (fwD) {
        map<string, float> w;
        for (int i = 0; i < store.size(); ++i)
            w[store[i]] = fwd[store[i]] * log((float)numberOfFiles / fwD);

        bool *isLooped = new bool[store.size()];
        for (int i = 0; i < store.size(); ++i)
            isLooped[i] = false;
        // find 5th max 
        for (int i = 0; i < 5; ++i) {
            int max = -1, index = -1;
            for (int j = 0; j < store.size(); ++j)
                if (!isLooped[j])
                    if (w[store[j]] > max) {
                        index = j;
                        max = w[store[j]];
                    }
            if (index != -1) {
                isLooped[index] = true;
                _5thLinks.push_back(store[index]);
            }
        }
    }
}

// Task 11
bool checkRangeOperator (string inputString) {
    regex operator_Range("(.*)(..)(.*)");
    if (regex_match(inputString, operator_Range))
        return true;
    return false;
}

void activateRangeOperator(TrieNode *root, string inputString, int numberOfFiles) {
    vector<string> listWords = splitOperator(inputString, '..');
    vector<string> _5thLinks;
    rankingRangeOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

void rankingRangeOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles) {
}

//----------------------------------
// Support func

// Split inputString -> vector [front of operator, behind of operator]
vector<string> splitOperator(string inputString, char oper) {
    vector<string> res;
    string temp;
    for (int i = 0; i < inputString.length(); ++i) {
        if (inputString[i] == ' ')
            continue;
        if (inputString[i] == oper) {
            res.push_back(temp);
            temp.clear();
        } else {
            temp += inputString[i];
            if (i == inputString.length() - 1)
                res.push_back(temp);
        }
    }
    return res;
}
