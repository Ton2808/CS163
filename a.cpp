#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
int main()
{
    vector<string> myvector;
    myvector.push_back("element");
    myvector.push_back("second");

 
    // using end() to print vector
    for (auto it = myvector.begin();
         it != myvector.end(); ++it)
        cout << ' ' << *it;
    auto it = myvector.end();

    cout << endl << *(it - 1) << endl;
    return 0;
}
