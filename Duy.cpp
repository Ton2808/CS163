#include "Duy.h"
#include "library.h"
using namespace std;

//Task 2 + 4 + 12

//Task 2: OR operator
bool checkOROperator(string inputString)
{
    regex operator_AND("[a-z]*[A-Z]*[0-9]*(\\s+)OR(\\s+)([a-z]*[A-Z]*[0-9]*)+");
    if (regex_match(inputString.begin(), inputString.end(), operator_AND))
        return true;
    return false;
}

vector<string> splitOROperator(TrieNode *root, string inputString)
{
    vector<string> res;
    string temp;
    for (int i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == ' ')
            continue;
        if (inputString[i] == 'OR')
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

