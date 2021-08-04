#include "Khoi.h"
#include "library.h"
using namespace std;
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
    regex checkCapital("[A-Z]");
    if (regex_match(word.substr(0, 1), checkCapital))
        word[0] += 32;
}

void getFilesToTrie(string fileName, ifstream &fin, TrieNode *&root, string stopWords[])
{
    fin.open(fileName);
    if (fin.is_open())
    {
        string tmp;
        while (!fin.eof())
        {
            fin.ignore();
            getline(fin, tmp);
            string word;
            regex checkLine("\\s*");
            if (regex_match(tmp, checkLine))
                break;
            istringstream in(tmp);
            while (getline(in, word, ' '))
            {
                regex checkWord("[A-Z]*[a-z]*[0-9]*");
                if (!regex_match(word, checkWord))
                    break;
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
    regex operator_Plus("[a-z]*[A-Z]*[0-9]*(\\s*)(\\+)(\\s*)[a-z]*[A-Z]*[0-9]*");
    if (regex_match(inputString, operator_Plus))
        return true;
    return false;
}

vector<string> splitPlusOperator(TrieNode *root, string inputString)
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
}

void activatePlusOperator(TrieNode *root, string inputString, int numberOfFiles)
{
    vector<string> listWords = splitPlusOperator(root, inputString);
    vector<string> _5thLinks;
    ranking(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

void ranking(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
{
    vector<pair<string, int> > *tmp;
    tmp = new vector<pair<string, int> >[word.size()];
    for (int i = 0; i < word.size(); ++i)
    {
        searchInTrieNode(root, word[i], tmp[i]);
    }
    // for (int i = 0; i < word.size(); ++i)
    // {
    //     cout << word[i] << '\n';
    //     for (int j = 0; j < tmp[i].size(); ++j)
    //     {
    //         cout << tmp[i][j].first << " " << tmp[i][j].second << '\n';
    //     }
    //     cout << '\n';
    // }
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
            //cout << i->first << fwd[i->first] << '\n';
        }
    }
    int fwD = store.size();
    //cout << fwD;
    if (fwD)
    {
        map<string, float> w;
        for (int i = 0; i < store.size(); ++i)
        {
            w[store[i]] = fwd[store[i]] * log((float)numberOfFiles / fwD);
            //cout << store[i] << " " << w[store[i]] << '\n';
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
            cout << a << '\n';
        }
        cout << '\n';
        cout << "------------------------------------------------------------------------------------------" << '\n';
        cout << '\n';
    }
    fin.close();
}