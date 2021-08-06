#include "Khoi.h"
#include "library.h"
using namespace std;
//------------------------------------------------------------------------------------------
//Set Up
void insertWordToTrie(TrieNode *&root, string a, string link)
{
    TrieNode *cur = root;
    for (int i = 0; i < a.length(); ++i)
    {
        int index = a[i];
        if (root == NULL)
        {
            root = new TrieNode(); // dummy Node
            root->children[index] = new TrieNode();
            cur = root->children[index];
        }
        else
        {
            if (!cur->children[index])
                cur->children[index] = new TrieNode();
            cur = cur->children[index];
        }
    }
    cur->isEndNode = true;
    int isAlreadyInVector_Index = -1;
    for (int i = 0; i < cur->links.size(); ++i)
    {
        if (link == cur->links[i].first)
        {
            isAlreadyInVector_Index = i;
            break;
        }
    }
    if (isAlreadyInVector_Index != -1)
        cur->links[isAlreadyInVector_Index].second++;
    else
        cur->links.push_back(make_pair(link, 1));
}
bool searchInTrieNode(TrieNode *root, string a, vector<pair<string, int> > &getLinks)
{
    int i = 0, index;
    while (i < a.length())
    {
        index = a[i];
        if (root->children[index] == NULL)
            return false;
        root = root->children[index];
        ++i;
    }
    if (!root->isEndNode)
        return false;

    for (int i = 0; i < root->links.size(); ++i)
        getLinks.push_back(root->links[i]);
    return true;
}

void setUpData(string dataFileName, ifstream &fin, string *&fileName, int &numberFiles)
{
    fin.open(dataFileName);
    if (fin.is_open())
    {
        numberFiles = count(istreambuf_iterator<char>(fin),
                            istreambuf_iterator<char>(), '\n');
        fin.seekg(0, fin.beg);

        fileName = new string[numberFiles];
        for (int i = 0; i < numberFiles; ++i)
        {
            getline(fin, fileName[i]);
        }
    }
    fin.close();
}

void getStringsStopWord(string fileStopWordName, string *&stopWord, ifstream &fin)
{
    int number;
    fin.open(fileStopWordName);
    if (fin.is_open())
    {
        fin >> number;
        stopWord = new string[number];
        for (int i = 0; i < number; ++i)
        {
            getline(fin, stopWord[i]);
            //cout << stopWord[i] << '\n';
        }
    }
    fin.close();
}

bool isStopWord(string stopWords[], string word, int number)
{
    for (int i = 0; i < number; ++i)
    {
        if (word == stopWords[i])
        {
            return true;
        }
    }
    return false;
}

void reConstructInput(string &word)
{
    regex checkCapital("(.*)[A-Z](.*)");
    if (regex_match(word, checkCapital))
    {
        for (int i = 0; i < word.size(); ++i)
        {
            if (word[i] <= 90 && word[i] >= 65)
            {
                word[i] += 32;
            }
        }
    }
}

void getFilesToTrie(string fileName, ifstream &fin, TrieNode *&root, string stopWords[])
{
    fin.open(fileName);
    if (fin.is_open())
    {
        string tmp;
        while (!fin.eof())
        {
            getline(fin, tmp);
            string word;
            regex checkLine("\\s*");
            if (regex_match(tmp, checkLine))
                break;
            istringstream in(tmp);
            while (in >> word)
            {
                regex checkWord("[A-Z]*[a-z]*[0-9]*");
                if (!regex_match(word, checkWord))
                    continue;
                reConstructInput(word);
                {
                    insertWordToTrie(root, word, fileName);
                    cout << word << '\n';
                    cout << fileName << '\n';
                    cout << '\n';
                }
            }
        }
    }
    fin.close();
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//Check Operator
bool checkANDOperator(string inputString)
{
    regex operator_AND("[a-z]*[A-Z]*[0-9]*(\\s+)AND(\\s+)([a-z]*[A-Z]*[0-9]*)+");
    if (regex_match(inputString.begin(), inputString.end(), operator_AND))
        return true;
    return false;
}

bool checkOROperator(string inputString)
{
    regex operator_AND("[a-z]*[A-Z]*[0-9]*(\\s+)OR(\\s+)([a-z]*[A-Z]*[0-9]*)+");
    if (regex_match(inputString.begin(), inputString.end(), operator_AND))
        return true;
    return false;
}

bool checkPlusOpertor(string inputString)
{
    regex operator_Plus("(.*)(\\+)(.*)");
    if (regex_match(inputString, operator_Plus))
        return true;
    return false;
}

bool checkExactlyOperator(string inputString)
{
    regex exactlyOperator("\"(.*)\"");
    if (regex_match(inputString, exactlyOperator))

        return true;
    return false;
}

bool checkWildCardOperator(string inputString)
{
    regex wildCardOperator("\"(.*)(\\*)(.*)\"");
    if (regex_match(inputString, wildCardOperator))
        return true;
    return false;
}

void checkOption(TrieNode *root, string inputString, int numberOfFiles)
{
    //1: And
    //2: Or
    //3: Minus
    //4: Intile:
    //5: Plus (Khoi)
    //6: filetype: txt
    //7: $ price
    //8: #hashtag
    //9: exactly search (Khoi)
    //10: searching with wildcards * (Khoi)
    //11: search in range $40..$50
    //12: enter ~to search synonym
    if (checkANDOperator(inputString))
    {
    }

    if (checkOROperator(inputString))
    {
    }

    if (checkPlusOpertor(inputString))
    {
        activatePlusOperator(root, inputString, numberOfFiles);
    }

    if (checkExactlyOperator(inputString))
    {
        if (checkWildCardOperator(inputString))
            acitvateWildCardOperator(root, inputString, numberOfFiles);
        else
            acitvateExactlyOperator(root, inputString, numberOfFiles);
    }
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//Wild Card * Operator
vector<string> splitWordInSpaceWildCard(string inputString, vector<int> &posAfter)
{
    vector<string> res;
    stringstream ss(inputString);
    string tmp;
    int index = 0;
    while (ss >> tmp)
    {
        if (tmp == "*")
        {
            posAfter.push_back(index);
            continue;
        }
        index++;
        res.push_back(tmp);
    }
    return res;
}

void acitvateWildCardOperator(TrieNode *root, string inputString, int numberOfFiles)
{
    inputString = inputString.substr(1, inputString.size() - 1);
    inputString = inputString.substr(0, inputString.size() - 1);
    vector<int> posOfStars;
    vector<string> keyWords = splitWordInSpaceWildCard(inputString, posOfStars);
    vector<string> _5thLinks;
    ranking_WildCardOperator(root, keyWords, _5thLinks, numberOfFiles, posOfStars);
    print(keyWords, _5thLinks);
}

void ranking_WildCardOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles, vector<int> starsPos)
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

    ifstream fin;
    vector<string> exactlyStore;
    for (int i = 0; i < store.size(); ++i)
    {
        fin.open(store[i]);
        if (fin.is_open())
        {
            string a = "(.*)";
            int index = 0;
            int j = 0;
            for (int i = 0; i < word.size(); ++i)
            {
                if (j < starsPos.size() && index == starsPos[j])
                {
                    i++;
                    a += "(.*)";
                }
                if (i != word.size() - 1)
                    a = a + word[i] + "(\\s+)";
                else
                    a += word[i];
                index++;
            }
            a += "(.*)";
            cout << a << '\n';
            regex matchString(a);
            while (!fin.eof())
            {
                string tmp;
                getline(fin, tmp);
                if (regex_match(tmp.substr(0, tmp.size() - 1), matchString))
                {
                    exactlyStore.push_back(store[i]);
                    break;
                }
            }
        }
        fin.close();
    }
    int fwD = exactlyStore.size();
    if (fwD)
    {
        map<string, float> w;
        for (int i = 0; i < exactlyStore.size(); ++i)
        {
            w[exactlyStore[i]] = fwd[exactlyStore[i]] * log((float)numberOfFiles / fwD);
        }
        bool *isLooped = new bool[exactlyStore.size()];
        for (int i = 0; i < exactlyStore.size(); ++i)
            isLooped[i] = false;
        for (int i = 0; i < 5; ++i)
        {
            int max = -1;
            int index = -1;
            for (int j = 0; j < exactlyStore.size(); ++j)
            {
                if (!isLooped[j])
                {
                    if (w[exactlyStore[j]] > max)
                    {
                        index = j;
                        max = w[exactlyStore[j]];
                    }
                }
            }
            if (index != -1)
            {
                isLooped[index] = true;
                _5thLinks.push_back(exactlyStore[index]);
            }
        }
    }
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//Exactly Operator

vector<string> splitWordInSpace(string inputString)
{
    vector<string> res;
    stringstream ss(inputString);
    string tmp;
    while (ss >> tmp)
    {
        res.push_back(tmp);
    }
    return res;
}

void acitvateExactlyOperator(TrieNode *root, string inputString, int numberOFiles)
{
    inputString = inputString.substr(1, inputString.size() - 1);
    inputString = inputString.substr(0, inputString.size() - 1);
    vector<string> keyWords = splitWordInSpace(inputString);
    vector<string> _5thLinks;
    ranking_ExactlyOperator(root, keyWords, _5thLinks, numberOFiles);
    print(keyWords, _5thLinks);
}

void ranking_ExactlyOperator(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
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

    ifstream fin;
    vector<string> exactlyStore;
    for (int i = 0; i < store.size(); ++i)
    {
        fin.open(store[i]);
        if (fin.is_open())
        {
            string a = "(.*)";
            for (int i = 0; i < word.size(); ++i)
            {
                if (i != word.size() - 1)
                    a = a + word[i] + "(\\s+)";
                else
                    a += word[i];
            }
            a += "(.*)";
            regex matchString(a);
            while (!fin.eof())
            {
                string tmp;
                getline(fin, tmp);
                if (regex_match(tmp.substr(0, tmp.size() - 1), matchString))
                {
                    exactlyStore.push_back(store[i]);
                    break;
                }
            }
        }
        fin.close();
    }
    int fwD = exactlyStore.size();
    if (fwD)
    {
        map<string, float> w;
        for (int i = 0; i < exactlyStore.size(); ++i)
        {
            w[exactlyStore[i]] = fwd[exactlyStore[i]] * log((float)numberOfFiles / fwD);
        }
        bool *isLooped = new bool[exactlyStore.size()];
        for (int i = 0; i < exactlyStore.size(); ++i)
            isLooped[i] = false;
        for (int i = 0; i < 5; ++i)
        {
            int max = -1;
            int index = -1;
            for (int j = 0; j < exactlyStore.size(); ++j)
            {
                if (!isLooped[j])
                {
                    if (w[exactlyStore[j]] > max)
                    {
                        index = j;
                        max = w[exactlyStore[j]];
                    }
                }
            }
            if (index != -1)
            {
                isLooped[index] = true;
                _5thLinks.push_back(exactlyStore[index]);
            }
        }
    }
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//Plus Operator
vector<string> splitPlusOperator(string inputString)
{
    vector<string> res;
    string temp;
    for (int i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == ' ')
            continue;
        if (inputString[i] == '+')
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

void activatePlusOperator(TrieNode *root, string inputString, int numberOfFiles)
{
    vector<string> listWords = splitPlusOperator(inputString);
    vector<string> _5thLinks;
    ranking_PlusOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
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
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//Print Function
void print(vector<string> keyWords, vector<string> _5thFiles)
{
    ifstream fin;
    for (int i = 0; i < _5thFiles.size(); ++i)
    {
        cout << _5thFiles[i] << '\n';
        printOneFile(_5thFiles[i], fin, keyWords);
    }
}

void printOneFile(string fileName, ifstream &fin, vector<string> keyWords)
{
    fin.open(fileName);
    if (fin.is_open())
    {
        string a;
        cout << "------------------------------------------------------------------------------------------" << '\n';
        while (!fin.eof())
        {
            getline(fin, a);
            stringstream ss(a);
            string tmp;
            while (ss >> tmp)
            {
                if (isHighLight(tmp, keyWords))
                {
                    cout << "\033[32m" << tmp << "\033[m"
                         << " ";
                }
                else
                    cout << tmp << " ";
            }
            cout << '\n';
        }
        cout << '\n';
        cout << "------------------------------------------------------------------------------------------" << '\n';
        cout << '\n';
    }
    fin.close();
}

bool isHighLight(string word, vector<string> keyWord)
{
    for (int i = 0; i < keyWord.size(); ++i)
        if (word == keyWord[i])
            return true;
    return false;
}
//------------------------------------------------------------------------------------------