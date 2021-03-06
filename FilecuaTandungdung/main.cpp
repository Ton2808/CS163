#include <iostream>
#include "library.h"
//#include "Tan.h"
#include "Khoi.h"
//#include "Duy.h"
//#include "Tin.h"
using namespace std;

int main()
{
    TrieNode *root = NULL;
    ifstream fin;

    //cached reference
    string *fileNames;
    string *stopWords;
    int numberFiles;

    setUpData("Search_Engine_Data/___index.txt", fin, fileNames, numberFiles);

    getStringsStopWord("StopWord.txt", stopWords, fin);

    fileNames = new string[3];
    fileNames[0] = "0.txt";
    fileNames[1] = "1111.txt";
    fileNames[2] = "1112.txt";
    numberFiles = 3;
    for (int i = 0; i < numberFiles; ++i)
    {
        getFilesToTrie("Search_Engine_Data/" + fileNames[i], fin, root, stopWords);
    }


    //configuration parameter

    // getFilesToTrie("Search_Engine_Data/" + fileNames[0], fin, root, stopWords);

    // cout << "input string: ";
    // string userInput;
    // getline(cin, userInput);
    // reConstructInput(userInput);
    // cout << userInput << '\n';
    // checkOption(root, userInput, numberFiles);

    while (true)
    {
        cout << "input string: ";
        string userInput;
        getline(cin, userInput);
        reConstructInput(userInput);
        cout << userInput << '\n';
        checkOption(root, userInput, numberFiles);
        int isClose = -1;
        cout << "wana close ? " << '\n';
        cin >> isClose;
        cin.ignore();
        if (isClose == 1)
            break;
    }
}
