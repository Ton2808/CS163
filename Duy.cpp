#include "Duy.h"
#include "Khoi.h"
#include "library.h"
using namespace std;

//Task 2 + 4 + 12

//Task 2: OR operator

vector<string> splitOROperator(string inputString)
{
    vector<string> res;
    string temp;
    for (int i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == ' ')
            continue;
        if (inputString[i] == 'O' && inputString[i + 1] == 'R')
        {
            res.push_back(temp);
            temp.clear();
            i += 2;
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
    bool check = false;
    for (int i = 0; i < word.size(); i++)
    {
        if (!tmp[i].empty())
        {
            check = true;
            break;
        }
    }
    if (check == false)
        return;
    //Calculate w for each document contained a, b and store link to string store
    set<string> store;
    map<string, float> w;
    for (int i = 0; i < word.size(); i++)
    {
        for (int j = 0; j < tmp[i].size(); j++)
        {
            //if link has both a and b then we sum their w.
            w[tmp[i][j].first] += tmp[i][j].second * log((float)numberOfFiles / tmp[i].size());
            store.insert(tmp[i][j].first);
            cout << tmp[i][j].first << endl;
        }
    }
    //Take 5th largest in w

    for (int i = 0; i < 5; i++)
    {
        int max = -1;
        set<string>::iterator itr, index;
        for (itr = store.begin(); itr != store.end(); itr++)
        {
            if (w[*itr] > max)
            {
                max = w[*itr];
                index = itr;
            }
        }
        _5thLinks.push_back(*index);
        store.erase(*index);
        if (store.empty())
            break;
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
void getTitleToFile(string fileName, TrieNode *&root, ifstream &fin)
{
    string link;
    string tmp;
    fin.open(fileName);
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            getline(fin, tmp);
            link = "Search_Engine_Data/" + tmp;
            tmp.erase(tmp.end() - 4, tmp.end());
            string word;
            istringstream in(tmp);
            while (in >> word)
            {
                regex checkWord("[A-Z]*[a-z]*[0-9]*");
                if (!regex_match(word, checkWord))
                    continue;
                reConstructInput(word);
                {
                    insertWordToTrie(root, word, link);
                    cout << word << '\n';
                    cout << link << '\n';
                    cout << '\n';
                }
            }
        }
    }
    else
        cout << "Error";
    fin.close();
}

bool checkIntitleOperator(string inputString)
{
    regex operator_INTITLE("(intitle:)(.*)");
    if (regex_match(inputString.begin(), inputString.end(), operator_INTITLE))
        return true;
    return false;
}

vector<string> splitIntitleOperator(string inputString)
{
    vector<string> res;
    inputString.erase(inputString.begin(), inputString.begin() + 8);
    string temp;
    for (int i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == ' ')
            continue;
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

void activateIntitleOperator(TrieNode *root, string inputString, int numberOfFiles)
{
    vector<string> listWords = splitIntitleOperator(inputString);
    vector<string> _5thLinks;
    ranking_PlusOperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}

//Task 12: ~ Synonymn
bool checkSynonymOperator(string inputString)
{
    regex operator_INTITLE("(~)(.*)");
    if (regex_match(inputString.begin(), inputString.end(), operator_INTITLE))
        return true;
    return false;
}

vector<string> getSynonymFromFile(string inputString, ifstream &fin)
{
    vector<string> store;
    inputString.erase(inputString.begin(), inputString.begin() + 1);
    fin.open("Synonym/" + inputString + ".txt");
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
                cout << word << endl;
                store.push_back(word);
            }
        }
    }
    else
        cout << "Error task 12 because of no file contained synonyms" << endl;
    fin.close();
    return store;
}

void activateSynonymOperator(TrieNode *root, string inputString, int numberOfFiles, ifstream &fin)
{
    vector<string> listWords = getSynonymFromFile(inputString, fin);
    vector<string> _5thLinks;
    ranking_OROperator(root, listWords, _5thLinks, numberOfFiles);
    print(listWords, _5thLinks);
}
