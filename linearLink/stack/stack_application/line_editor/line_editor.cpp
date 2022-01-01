#include <iostream>
using namespace std;
#include <stack>

//using '&' as the end of a text.
void LineEdit()
{
    stack<char> line;
    char inputch;
    char tempchar;
    cin >> inputch;
    while( inputch != EOF )
    {
        while( inputch != EOF && inputch != '\n' )
        {
            switch(inputch)
            {
                // delete a char
                case '#' :
                    tempchar = line.top();
                    line.pop();
                    cout << "debug1: delete a char " << tempchar << endl;
                    break;
                // delete a line
                case '@' :
                    while( ! line.empty() )
                    {
                        tempchar = line.top();
                        line.pop();
                        cout << "debug2: delete a char of the whole line " << tempchar << endl;
                    }
                    break;
                // valid char input
                default:
                    line.push(inputch);
                    cout << "debug3: push the " << inputch << " into the stack.\n";
                    break;
            }
            cin >> inputch;
        }
        //clear the stack
        while( ! line.empty() )
        {
            line.pop();
        }
        if( inputch != EOF )
            cin >> inputch;
    } 
}

int main()
{
    cout << "please input a text.\n";
    LineEdit();
    cout << "done!\n";
}