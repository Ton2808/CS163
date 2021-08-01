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

void getFilesToTrie(string fileName, ifstream &fin, TrieNode *&root, string stopWords[])
{
    fin.open(fileName);
    if (fin.is_open())
    {
        cout << "can open file" << '\n';
        string tmp;
        while (!fin.eof())
        {
            getline(fin, tmp);
            string word;
            stringstream in(tmp);
            while (getline(in, word, ' '))
            {
                //if (!isStopWord(stopWords, word, 173))
                insertWordToTrie(root, word, fileName);
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

vector<int> checkOption(string inputString)
{
    vector<int> arrSolutions;
    //1: And
    //2: Or
    //3: Minus
    //4: Intile:
    //5: Plus
    //6: filetype: txt
    //7: $ price
    //8: #hashtag
    //9: exactly search
    //10: searching with wildcards *
    //11: search in range $40..$50
    //12: enter ~to search synonym
    if (checkANDOperator(inputString))
        arrSolutions.push_back(1);
    return arrSolutions;
}