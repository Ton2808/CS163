#include "Tin.h"

//----------------------------------------------------------------
// Task 3

bool checkMinusOperator(string inputString)
{
    regex operator_Minus("(.*)( -)(.*)");
    if (regex_match(inputString, operator_Minus))
        return true;
    return false;
}

void activateMinusOperator(TrieNode *root, string inputString, int numberOfFiles)
{
    vector<string> listWords = splitOperator(inputString, '-');
    vector<string> _5thLinks;
    rankingMinusOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

void rankingMinusOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
{
    vector<pair<string, int> > *tmpActive;
    vector<pair<string, int> > *tmpMinus;

    int numActive = 1;
    int numMinus = word.size() - 1;

    tmpActive = new vector<pair<string, int> >[numActive];
    tmpMinus = new vector<pair<string, int> >[numMinus];

    // Get all the links in the trie
    for (int i = 0; i < numActive; ++i)
        searchInTrieNode(root, word[i], tmpActive[i]);
    for (int i = 1; i < numMinus; ++i)
        searchInTrieNode(root, word[i], tmpMinus[i]);

    map<string, int> checkAllWordIsInFile;
    map<string, int> fwd;

    for (int i = 0; i < numMinus; ++i)
        for (int j = 0; j < tmpMinus[i].size(); ++j)
            checkAllWordIsInFile[tmpMinus[i][j].first]--;

    vector<string> store;
    for (int i = 0; i < numActive; ++i)
        for (int j = 0; j < tmpActive[i].size(); ++j)
            if (checkAllWordIsInFile[tmpActive[i][j].first] == 0)
                fwd[tmpActive[i][j].first] += tmpActive[i][j].second;

    for (map<string, int>::iterator i = fwd.begin(); i != fwd.end(); ++i)
        store.push_back(i->first);

    _5thLinks = find_5thLinks(fwd, store, numberOfFiles);
}

//----------------------------------------------------------------
// Task 8
bool checkHashtagsOperator(string inputString)
{
    regex operator_Hashtags("(#)(.*)");
    if (regex_match(inputString, operator_Hashtags))
        return true;
    return false;
}

void activateHashtagsOperator(TrieNode *root, string inputString, int numberOfFiles)
{
    vector<string> listWords = splitOperator(inputString, '#');
    vector<string> _5thLinks;
    rankingHashtagsOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

void rankingHashtagsOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
{
    // Assume that the input string: "#hashtags #ahldklsf #jksndkgal ..."
    vector<pair<string, int> > *tmp;
    tmp = new vector<pair<string, int> >[word.size()];
    // Get all the links in the trie
    for (int i = 0; i < word.size(); ++i)
        searchInTrieNode(root, "#" + word[i], tmp[i]);

    map<string, int> checkAllWordIsInFile;
    map<string, int> fwd;

    for (int i = 0; i < word.size(); ++i)
        for (int j = 0; j < tmp[i].size(); ++j)
            fwd[tmp[i][j].first] += tmp[i][j].second;

    vector<string> store;
    for (map<string, int>::iterator i = fwd.begin(); i != fwd.end(); ++i)
        store.push_back(i->first);

    _5thLinks = find_5thLinks(fwd, store, numberOfFiles);
}

// Task 11
/* 
Assume that the input String: "something $123..$345"
    call input string like that: "A B..C"
*/
bool checkRangeOperator(string inputString)
{
    regex operator_Range("(.*)(\\..)(.*)");
    if (regex_match(inputString, operator_Range))
        return true;
    return false;
}

vector<string> splitDoubleDotOperator(string inputString)
{
    vector<string> res;
    string temp;
    for (int i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == ' '){
            res.push_back(temp);
            temp.clear();
        }
            
        if (inputString[i] == '.' && inputString[i + 1] == '.')
        {
            ++i;
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

void activateRangeOperator(TrieNode *root, string inputString, int numberOfFiles)
{
    vector<string> listWords = splitDoubleDotOperator(inputString);
  
    vector<string> _5thLinks;
    rankingRangeOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
} // List Words = [A, B, C]

void rankingRangeOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
{
    int pricePos = word.size() - 2;
    int minPrice = stoi(word[pricePos]);
    int maxPrice = stoi(word[pricePos + 1]);
    int num = pricePos + maxPrice - minPrice;

    cout << "Price: " << num << endl;

    vector<pair<string, int> > *tmp;
    tmp = new vector<pair<string, int> >[num];

    // Get all the links in the trie
    for (int i = 0; i < pricePos; ++i)
        searchInTrieNode(root, word[i], tmp[i]);

    for (int i = pricePos; i < num; ++i) {
        searchInTrieNode(root, to_string(minPrice + i - pricePos), tmp[i]);
    }

    map<string, int> checkTrueFinding;
    map<string, int> fwd;

    for (int i = 0; i < pricePos; ++i)
        for (int j = 0; j < tmp[i].size(); ++j)
        {
            fwd[tmp[i][j].first] += tmp[i][j].second;
            checkTrueFinding[tmp[i][j].first] += 1;
        }

    for (int i = pricePos; i < num; ++i)
        for (int j = 0; j < tmp[i].size(); ++j)
            if (checkTrueFinding[tmp[i][j].first] == pricePos)
            {
                checkTrueFinding[tmp[i][j].first] = -1; // correct link
                fwd[tmp[i][j].first] += tmp[i][j].second;
            }

    vector<string> store;
    for (map<string, int>::iterator it = checkTrueFinding.begin(); it != checkTrueFinding.end(); ++it)
        if (it->second == -1)
            store.push_back(it->first);

    _5thLinks = find_5thLinks(fwd, store, numberOfFiles);
}

//----------------------------------
// Support func

// Split inputString -> vector [front of operator, behind of operator]
vector<string> splitOperator(string inputString, char oper)
{
    vector<string> res;
    string temp;
    for (int i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == ' ')
            continue;
        if (inputString[i] == oper)
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

/* 
Note:
    - fwd: 
    - store: 
    - numberOfFiles: the total files we have 
*/
vector<string> find_5thLinks(map<string, int> fwd, vector<string> store, int numberOfFiles)
{
    int fwD = store.size();
    vector<string> _5thLinks;

    if (fwD)
    {
        map<string, float> w;
        for (int i = 0; i < store.size(); ++i)
            w[store[i]] = fwd[store[i]] * log((float)numberOfFiles / fwD);

        bool *isLooped = new bool[store.size()];
        for (int i = 0; i < store.size(); ++i)
            isLooped[i] = false;
        // find 5th max
        for (int i = 0; i < 5; ++i)
        {
            int max = -1, index = -1;
            for (int j = 0; j < store.size(); ++j)
                if (!isLooped[j])
                    if (w[store[j]] > max)
                    {
                        index = j;
                        max = w[store[j]];
                    }
            if (index != -1)
            {
                isLooped[index] = true;
                _5thLinks.push_back(store[index]);
            }
        }
    }
    return _5thLinks;
}
