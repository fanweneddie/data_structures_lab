//Writing the body of the functions in the head file Backtrack
//And using it to solve the specific maze problem.

#include "BackTrack.h"
#include "Maze.cpp"

/*
    constructor using app to initialize this BackTrack object
*/
BackTrack::BackTrack(const Application& app)
{
    this->app = app;
}


/*
    CORE FUNCTION FOR THE BACKTRACK PURPOSE.
    Try to find a way out.if successful, return true.
*/
bool BackTrack::try_to_solve(Position Pos)
{
    bool success = false;
    Application::Iterator itr(Pos);
    cout << "debug9.1: the pos of itr is " << itr.get_pos().get_row()
         << " " << itr.get_pos().get_column() << endl;


    Position upPosition(Pos.get_row() - 1 , Pos.get_column(),2 );
    cout << "debug1.1: upPosition " << upPosition.get_row() 
        << " " << upPosition.get_column() << endl;

    Position westPosition(Pos.get_row(), Pos.get_column() - 1, 1);
    cout << "debug1.2: westPosition " << westPosition.get_row() 
        << " " << westPosition.get_column() << endl;
    while( !success && !itr.at_end() )
    {
       // cout << "debug3: the itr pos is: " << itr.get_pos().get_row()
         //        << " " << itr.get_pos().get_column() << endl;
        if (app.valid(upPosition))
        {
            cout << "debug4: up is valid\n";
            itr.upward();
            Position posOfItr = itr.get_pos();
            cout << "debug5: the position after upward " << posOfItr.get_row()
                 << " " << posOfItr.get_column() << endl;
            
            app.record( posOfItr );
            cout << "debug8: have recorded\n";
            if( app.done( posOfItr ) )
            {
                
                success = true;
            }
            else
                //the recursion of the function
                success = try_to_solve(posOfItr);
        }

        cout << "debug9.2: the pos of itr is " << itr.get_pos().get_row()
                 << " " << itr.get_pos().get_column() << endl;

        cout << "debug9.3: the pos of westPosition is " << westPosition.get_row()
             << " " << westPosition.get_column() << endl;
        if( app.valid(westPosition) )
        {
            cout << "debug9: west is valid\n";
            
                 
            itr.westward();
            Position posOfItr = itr.get_pos();
            cout << "debug9.5: after westward " << posOfItr.get_row()
                 << " " << posOfItr.get_column() << endl;
            
            app.record( posOfItr );
            if( app.done( posOfItr ) )
                success = true;
            else
                //the recursion of the function
                success = try_to_solve( posOfItr );
        }

        else
        {
            if(!success)
            {
            //backtrack
            //cout << "debug11: backtrack.\n";
                cout << "debug10.1 : enter backtrack\n";
                cout << "debug before backtrack: the pos of itr is " << itr.get_pos().get_row()
                 << " " << itr.get_pos().get_column() << endl;
                
                cout << "ANOTHER debug before backtrack: the pos of itr is " << Pos.get_row()
                 << " " << Pos.get_column() << endl;

                app.undo(Pos);
                itr.go_back();
                cout << "debug after backtrack: the pos of itr is " << itr.get_pos().get_row()
                 << " " << itr.get_pos().get_column() << endl;

                cout << "debug10.2 : have backtracked\n";
                cout << "debug 10.3\n";
                break;
            }
        }
        
    }
    return success;
}