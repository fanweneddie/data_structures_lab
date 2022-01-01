#include "editor.cpp"
#include <iostream>
using namespace std;

int main()
{
    const string PROMPT = "PLEASE ENTER A LINE: ";
    const string CLOSE_WINDOW_PROMPT 
        = "PLEASE PRESS ANY KEY TO CLOSE THE WINDOW: ";
    Editor editor;
    string result;
    string line;
    do
    {
        cout << PROMPT << endl;
        getline(cin, line);
        result = editor.parse(line);

        //if the insert, line and delete command is valid    
        if( result.substr(0,1) != COMMAND_START 
                && result.substr(0,1) != "H" )
            cout << SUCCESSFUL_INPUT << endl;
        //if the first char is 'H',
        //a final text is required to be printed
        //if the fist char is COMMAND_START
        //print the error info
        else 
        {
            cout << result << endl;
        }
    }while(line != DONE_COMMAND);

    cout << CLOSE_WINDOW_PROMPT << endl;
    cin.get();
    return 0;
}