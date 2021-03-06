#include <iostream>
#include "library.h"
//#include "Tan.h"
#include "Khoi.h"
#include "Duy.h"
//#include "Tin.h"
using namespace std;

int main()
{
    TrieNode *root = NULL;
    TrieNode *rootTitle = NULL;
    ifstream fin;

    //cached reference
    string *fileNames;
    string *stopWords;
    int numberFiles;

    cout << "ok" << '\n';
    setUpData("Search_Engine_Data/___index.txt", fin, fileNames, numberFiles);

    getStringsStopWord("StopWord.txt", stopWords, fin);

    for (int i = 0; i < numberFiles; ++i)
    {
        getFilesToTrie("Search_Engine_Data/" + fileNames[i], fin, root, stopWords);
    }

    getTitleToFile("Search_Engine_Data/___index.txt", rootTitle, fin);
    //configuration parameter

    // getFilesToTrie("Search_Engine_Data/" + fileNames[0], fin, root, stopWords);

    // cout << "input string: ";
    // string userInput;
    // getline(cin, userInput);
    // reConstructInput(userInput);
    // cout << userInput << '\n';
    // checkOption(root, userInput, numberFiles);

    vector<string> isSearched;
    while (true)
    {
        cout << "input string: ";
        string userInput;
        getline(cin, userInput);

        if (!checkOROperator(userInput))
        {
            reConstructInput(userInput);
        }

        //reConstructInput(userInput);

        if (checkHistoryOption(userInput))
        {
            isSearched.push_back(userInput.substr(1, userInput.size() - 1));
            activateHistory(isSearched, userInput);
        }
        else
            isSearched.push_back(userInput);

        cout << userInput << '\n';
        checkOption(root, rootTitle, userInput, numberFiles);
        int isClose = -1;
        cout << "wana close ? " << '\n';
        cin >> isClose;
        cin.ignore();
        if (isClose == 1)
            break;
    }
}
