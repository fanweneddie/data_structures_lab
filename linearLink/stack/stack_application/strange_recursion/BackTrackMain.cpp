#include <iostream>
#include <string>
#include "BackTrack.cpp"
using namespace std;

int main()
{
    const string WELCOME = "Welcome to the maze game!!!";
    const string INITIAL_STATE = "The initial state is as follows: ";
    const string SUCCESS_STATE = "A solution has been found.";
    const string FAILURE = "There is no solution.";
    const string CLOSE = "please press the key to close the window.";


    Application maze;
    BackTrack bt(maze);
/*    
    cout << WELCOME << endl;
    cout << INITIAL_STATE << endl;
    cout << maze << endl;
*/  
    Position start = maze.generate_initial_state();

    if( ! maze.valid(start) )
    {
        cout << FAILURE << endl;
    }
    else
    {
        maze.record(start);
        
        if( maze.done(start) || bt.try_to_solve(start) )
        {
            cout << SUCCESS_STATE << endl;
        }
        else
        {
            maze.undo(start);
            cout << FAILURE << endl;
        }
    }
    cout << endl
         << endl
         << CLOSE;
    cin.get();
    return 0;
}