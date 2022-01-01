#include <iostream>
#include <deque>
#include <string>
using namespace std;

bool check_palindrome(const string& inputString)
{
    deque<char> analysis;
    auto itr = inputString.begin();
    for (; itr != inputString.end();++itr)
    {
        analysis.push_back(*itr);
    }

    while( !analysis.empty() )
    {
        if( analysis.front() != analysis.back() )
            return false;
        else
        {
            analysis.pop_front();
            if(!analysis.empty())
                analysis.pop_back();
        }
    }
    return true;
}

int main()
{
    string originString;
    int choice;
    while(1)
    {
    cout << "please input a string to check whether it is palindrome.\n";
    cin >> originString;
    if( check_palindrome(originString) )
        cout << "this string is a palindrome string.\n";
    else
        cout << "this string is not a palindrome string.\n";
    cout << "enter 0 to quit.\n";
    cin >> choice;
    if(choice == 0)
        break;
    }
    return 0;
}