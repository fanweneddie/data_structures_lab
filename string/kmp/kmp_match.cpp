#include <iostream>
using namespace std;
#include <string>
#include <vector>

void get_next(string p , vector<int>& next)
{
    next[0] = -1;
    int k = -1, len = p.length();
    for (int i = 1; i < len;++i)
    {
        while( k> -1 && p[i] != p[k+1] )
        {
            k = next[k];
        }
        if( p[k+1] == p[i] )
        {
            next[i] = ++k;
        }
        else
        {
            next[i] = k;
        }
    }
}

int kmp(const string& s, const string& p)
{
    if( p.empty() )
        return 0;
    int sLen = s.length(), pLen = p.length();
    if( sLen < pLen )
        return -1;
    vector<int> next;
    //get_next(p, next);
    next.push_back(-1);
     next.push_back(0);
      next.push_back(0);
       next.push_back(0);
     next.push_back(0);
      next.push_back(1);
       next.push_back(2);
    cout << "the next array is "  << endl;
    for (auto itr = next.begin(); itr != next.end();++itr)
    {
        cout << *itr << endl;
    }

}

int main()
{
    string mainString, subString;
    cout << "please input the mainstring.\n";
    mainString = "BBC_ABCDAB_ABCDABCDABDE";
    cout << "please input the substring.\n";
    subString = "ABCDABD";
    int pos = kmp(mainString,subString);
    if(pos == -1)
        cout << "not a substring.\n";
    else
        cout << "is the substring starting from " << pos << endl;
    return 0;
}