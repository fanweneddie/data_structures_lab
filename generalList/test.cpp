#include "generalList.h"

int main()
{
    string str;
    cout << "please input the string.\n";
    cin >> str;
    if( !check_bracket(str) )
    {
        cout << "the input expression is not valid.\n";
        exit(0);
    }
    GeneralList gl(str);
    cout << gl;
}