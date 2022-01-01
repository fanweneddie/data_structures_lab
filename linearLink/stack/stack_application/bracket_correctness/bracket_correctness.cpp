#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool match(const char & charA, const char& charB)
{
    return (charA == '(' && charB == ')') ||
           (charA == '[' && charB == ']') ||
           (charA == '{' && charB == '}');
}

int bracket_type(const char& charA)
{
    //left bracket
    if( charA == '(' || charA == '[' || charA == '{' )
        return 1;
    //right bracket
    if( charA == ')' || charA == ']' || charA == '}' )
        return 2;
    //other char
    else
        return 0;
}
int main()
{
    string expression;
    stack<char> bracketCheck;
    //push '#' into the bottom of the stack to check whether it is legal at last
    bracketCheck.push('#');
    string choice;
    while(choice != "q")
    {
    cout << "please input an expression with brackets.";
    cout <<" we will check its correctness.\n" ;
    cin >> expression;
    for( string::iterator itr = expression.begin();
            itr != expression.end();++itr )
    {
        // *itr is left bracket,push it into the stack
        if( bracket_type(*itr) == 1 )
        {
            bracketCheck.push(*itr);
        }
        else 
        {
            //*itr is right bracket
            if( bracket_type(*itr) == 2 )
            {
                // if match, pop the corresponding left bracket.
                if( match(bracketCheck.top(),*itr) )
                    bracketCheck.pop();
                else // no match, so the expression is illegal.
                {
                    bracketCheck.push(*itr);// cover the '#' and make the result illegal
                    break;
                }
            }
        }//else
        cout << "debug: now the top element is " << bracketCheck.top() << endl;
    }//for

    if(bracketCheck.top() == '#')
        cout << "legal expression.\n";
    else
        cout << "illegal expression.\n";
    cout << "press q to quit or any other key to continue.\n";
    cin >> choice;
    }
    return 0;
}