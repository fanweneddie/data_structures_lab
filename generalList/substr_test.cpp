#include <iostream>
#include <string>
#include <stack>
using namespace std;


string delete_bracket(string s, int iLeft)
{
    stack<char> bracketStore;
    bracketStore.push('(');
    int len = s.length();
    for (int i = iLeft + 1; i < len;++i)
    {
        if( s[i] == '(')
        {
            bracketStore.push('(');
        }
        else if( s[i] == ')')
        {
            bracketStore.pop();
            if( bracketStore.empty() )
            {
                return s.substr(i + 1);
            }
        }//else if
    }//for
    return s;
}

int main()
{
    string s1 = "ab(ad)aa";
    string s2 = delete_bracket(s1,2);
    cout << s2 << endl;
}