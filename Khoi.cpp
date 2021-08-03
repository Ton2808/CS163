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
                {
                    break;
                }

                if (!isStopWord(stopWords, word, 202))
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
    regex operator_Plus("[a-z]*[A-Z]*[0-9]*(\\S*)(\\+)(\\S*)[a-z]*[A-Z]*[0-9]*");
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
    //print(listWords, _5thLinks);
}

void ranking(TrieNode *root, vector<string> word, vector<string> &_5thLinks, int numberOfFiles)
{
    vector<pair<string, int> > tmp;
    for (int i = 0; i < word.size(); ++i)
    {
        searchInTrieNode(root, word[i], tmp);
    }
    for (int i = 0; i < tmp.size(); ++i)
    {
        cout << tmp[i].first << " " << tmp[i].second << '\n';
    }
}

void print(vector<string> keyWords, vector<string> _5thFiles)
{
}