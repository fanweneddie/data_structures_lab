#include <iostream>
#include <cstring>
using namespace std;
//the worstTime is  O(m*n).
int violent_match( char *s,char *p,int pos)
{
    int sLen = strlen(s), pLen = strlen(p);
    int i = pos, j = 0;
    while(i < sLen  && j < pLen )
    {
        if( s[i] == p[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i = i - j + 2;
            j = 0;
        }
    }

    if( j == pLen)
    {
        return i - pLen;
    }
    else
        return -1;
}

int main()
{
    char mainString[10], subString[5];
    cout << "please input a main string.\n";
    cin >> mainString;
    cout << "please input a string to check whether it is the substring.\n";
    cin >> subString;
    int pos = violent_match(mainString, subString, 0);
    cout << pos << endl;
}