#include <iostream>
using namespace std;
#include <string>
#include <vector>

//creating the corresponding next array according to the pattern string p.
/*
e.g.
    index 0  1 2 3 4 5
    p     a  b a a b c
    next  -1 0 0 1 1 2
    next[4] means if x != p[4], 
    //we need to slide the p to compare p[ next[4] ](that is p[1]) and x.
*/
void get_next(string p , vector<int>& next)
{
    // let next[0] = -1.
    next[0] = -1;
    int k = 0, len = p.length();
    for (int i = 1; i < len;++i)
    {
        k = next[i - 1];
        //case1 : there is no same prefix or samefix
        // slide p to let p[0] compare with x.
        if(k == -1)
        {
            next[i] = 0;
            continue;
        }
        //case2: e.g. p: abcabc for p[5] ='c',(i = 5)
        // k = next[4] = 1. since p[1] = p[5-1] = 'b'.
        // next[5] = next[4] + 1 = 2.
        if( p[i-1] == p[k] )
        {
            next[i] = k + 1;
        } 
        //case 3: not so asymmetrical.
        //e.g. checking whether the substring of p0p1p2...pk-1 can match the p[i-1].
        //if so, we can let next[i] = k+1.
        //else: checking the substring of the substring( iteration ) 
        // until k == -1 ( can't find the substring)
        else
        {
            while( k != -1 && p[i-1] != p[k] )
            {
                k = next[k];
            }
            next[i] = k + 1;
        }
    }//for
}
/*
kmp: matching function
input : mainstring s,checkedstring p and the starting position to check.
output : if p is the substring of s, return the index of the first char of p in s.
        if not,return -1;
        if the starting Pos >= s.len , throw an exception.
Since the kmp only traverse every chars in the mainstring, the worstTime of 
kmp is O(mainstring.len). 
( Since checkedstring.len << mainstring.len, the time spent in building next array 
can be ignored) 
*/
int kmp(const string& s, const string& p,int startPos)
{
    //first,dealing with some easy and special circumstances.
    if( p.empty() )
        return 0;
    int sLen = s.length(), pLen = p.length();
    if( sLen < pLen )
        return -1;
    if( startPos >= sLen )
        throw "the startPosition is out of range.\n";
    //creating next array.
    vector<int> next(pLen + 1);
    get_next(p, next);

    int i = startPos, j = 0;
    while( i < sLen && j < pLen )
    {
        //case 1: current char is matched 
        //  or the j = -1(have to match p from the its begining)
        if(j == -1 || s[i] == p[j] )
        {
            ++i;
            ++j;
        }
        //case2: mismatch occurs but we can find the same prefix and postfix,
        // so we can slide the p .
        else
        {
            j = next[j];
        }
    }//while
    if( j >=pLen )
        return i - pLen;
    else
        return -1;

}
/* the testing data:
s = ABAABABAABBABAABC
p = ABAABC
*/

int main()
{
    string mainString, checkedString;
    cout << "please input the mainString.\n";
    cin >> mainString;
    cout << "please input the checkedString.\n";
    cin >> checkedString;
    cout << "begin matching the string.\n";
    int pos;
    try
    {
        pos = kmp(mainString, checkedString, 30);
        if(pos == -1)
            cout << "not a substring.\n";
    else
        cout << "is the substring starting from " << pos << endl;
    }
    catch( const char* s)
     {
         cout << "exception thrown.\n";
         cout << s << endl;
     }   
    
    return 0;
}