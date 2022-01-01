//The program for the specific maze problem
#include <iostream>
#include "Application.h"
using namespace std;

const int WALL = 0;
const int CORRIDOR = 1;
const int PATH = 9;
const int TRIED = 2;
const int ROWS = 7;
const int COLUMNS = 13;
int grid[ROWS][COLUMNS] =
    {
        {1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
//storing the fromDirection of every position
int ArrayOfFromDirection[ROWS][COLUMNS];
Position start, finish;

/*store the fromDirection of Pos*/
void recordFromDirection(const Position& Pos)
{
    ArrayOfFromDirection[ Pos.get_row() ][ Pos.get_column() ] 
            = Pos.get_fromDirection();
}


//itrfield

/*
using some input to generate the initial state and
return a position object of the start.
*/
Position Application::generate_initial_state()
{
    const string START_PROMPT 
        = "please enter the start row and start column: ";
    const string FINISH_PROMPT 
        = "please enter the finish row and finish column: ";
    int row, column;
    
    cout << START_PROMPT << endl;
    //cin >> row >> column;
    row = 1;
    column = 4;
    start.set_position(row, column,2);
    recordFromDirection(start);

    cout << FINISH_PROMPT << endl;
    //cin >> row >> column;
    //cin.get();
    row = 0;
    column = 0;
    finish.set_position(row,column,2);
    recordFromDirection(finish);
    return start;
}

/*
    If the position is on the way to the destination,return true
    And so and so forth.
*/
bool Application::valid(const Position& Pos) const
{
    //the position is within the range and is one the corridor
    if( Pos.get_row()  >=0 && Pos.get_row() < ROWS 
        && Pos.get_column() >=0 && Pos.get_column() < COLUMNS
        && grid[ Pos.get_row() ][ Pos.get_column() ] == CORRIDOR )
        return true;
    else
        return false;
}

 /*
recording the position(if this is valid)
(maybe) by changing one of its flag.
*/
void Application::record(const Position &Pos)
{
    cout << "debug enter record : the row and column is "
         << Pos.get_row() << " " << Pos.get_column() << endl;
    grid[Pos.get_row()][Pos.get_column()] = PATH;

    cout << "debug of record " << Pos.get_row()
         << " " << Pos.get_column() << " "
         << grid[Pos.get_row()][Pos.get_column()] << endl;
} 

/*
If the position is the destination,return true
And so and so forth.
*/
bool Application::done(const Position &Pos) const
{
    return ( Pos.get_row() == finish.get_row() 
    && Pos.get_column() == finish.get_column() );
}

/*
recording the position that is not on the way to the destination
*/
void Application::undo(const Position &Pos)
{
    grid[Pos.get_row()][Pos.get_column()] = TRIED;
}

/*
output the circumstance of a state in the application.
*/
ostream& operator << (ostream& out , Application& app)
{
    out << endl;
    for(int row = 0; row < ROWS ; row++)
    {
        for (int column = 0;column < COLUMNS; column++)
        {
            out << grid[row][column] << " ";
        }
        out << endl;
    }
    return out;
}

/*
constructor with the argument of a position
*/
Application::Iterator::Iterator( Position Pos)
{
    posPtr = &Pos;
}

/*override function of reassignment*/
Application::Iterator& Application::Iterator::
            operator=(const Iterator& iter)
{
    cout << "DEBUG: enter =\n";
    int newRow = iter.posPtr->get_row();
    int newColumn = iter.posPtr->get_column();
    int newFromDirection = iter.posPtr->get_fromDirection();
    cout << "second debug of =\n";
    posPtr->set_position(newRow, newColumn, newFromDirection);
    cout << "third debug: the new element is" << posPtr->get_row()
        << " " << posPtr->get_column()
        << " " << posPtr->get_fromDirection() << endl;
    return *this;
}
/*
itr++ to make it go upward
*/               
void Application::Iterator::upward()
{
    cout << "debug start upward\n";
    Position newPos( this -> posPtr -> get_row() -1 ,
                    this -> posPtr -> get_column(),2 );
    recordFromDirection(newPos);
    cout << "debug in the upward "
         << "the new pos is "
         << newPos.get_row() << " " << newPos.get_column() << endl;
    this -> posPtr = &newPos;
}


/*
iterator-- to make it go downwards
*/               
void Application::Iterator::downward()
{
    cout << "debug start downward\n";
    Position newPos( this -> posPtr -> get_row() + 1 ,
                    this -> posPtr -> get_column(),0 );
    recordFromDirection(newPos);
    cout << "debug in the downward "
         << "the new pos is "
         << newPos.get_row() << " " << newPos.get_column() << endl;
    this -> posPtr = &newPos;
}

/*
itr++ to make it go westward
*/               
void Application::Iterator::westward()
{
    cout << "debug start westward\n";
    Position newPos( this -> posPtr -> get_row() ,
                    this -> posPtr -> get_column()-1, 1);
    recordFromDirection(newPos);
    cout << "debug in the westward "
         << "the new pos is "
         << newPos.get_row() << " " << newPos.get_column() << endl;
    this->posPtr = &newPos;
}

/*
itr-- to make it go eastward
*/               
void Application::Iterator::eastward()
{
    cout << "debug start eastward\n";
    Position newPos( this -> posPtr -> get_row() ,
                    this -> posPtr -> get_column() + 1 ,3);
    recordFromDirection(newPos);
    cout << "debug in the eastward "
         << "the new pos is "
         << newPos.get_row() << " " << newPos.get_column() << endl;
    this->posPtr = &newPos;
}




/*
iterator-- to make it go upwards back
*/       
Application::Iterator Application::Iterator::back_upward()
{
    cout << "debug start BACK upward\n";
    int nextRow = this -> posPtr -> get_row() - 1;
    int nextColumn = this->posPtr->get_column();
    Position newPos( nextRow, nextColumn, ArrayOfFromDirection[nextRow][nextColumn] );
    cout << "debug in the back upward "
         << "the new pos is "
         << newPos.get_row() << " " << newPos.get_column() << endl;
    Application::Iterator newItr(newPos);
    return newItr;
}

/*
iterator-- to make it go downwards back
*/       
Application::Iterator Application::Iterator::back_downward()
{
    cout << "debug start BACK downward\n";
    int nextRow = this -> posPtr -> get_row() + 1;
    int nextColumn = this->posPtr->get_column();
    Position newPos( nextRow, nextColumn, ArrayOfFromDirection[nextRow][nextColumn] );
    cout << "debug in the back downward "
         << "the new pos is "
         << newPos.get_row() << " " << newPos.get_column() << endl;

    Application::Iterator newItr(newPos);

    cout << "debug2 in the back downward "
         <<"newItr is " << newItr.posPtr->get_row() << " " << newItr.posPtr->get_column() << endl;
    return newItr;
}

/*
iterator-- to make it go westwards back
*/       
Application::Iterator Application::Iterator::back_westward()
{
    cout << "debug start BACK westward\n";
    int nextRow = this -> posPtr -> get_row();
    int nextColumn = this->posPtr->get_column() + 1;
    Position newPos( nextRow, nextColumn, ArrayOfFromDirection[nextRow][nextColumn] );
    cout << "debug in the back westward "
         << "the new pos is "
         << newPos.get_row() << " " << newPos.get_column() << endl;
    
    Application::Iterator newItr(newPos);
    return newItr;   
}

/*
iterator-- to make it go eastwards back
*/       
Application::Iterator Application::Iterator::back_eastward()
{
    cout << "debug start BACK eastward\n";
    int nextRow = this -> posPtr -> get_row();
    int nextColumn = this->posPtr->get_column() - 1;
    Position newPos( nextRow, nextColumn, ArrayOfFromDirection[nextRow][nextColumn] );
    cout << "debug in the back eastward "
         << "the new pos is "
         << newPos.get_row() << " " << newPos.get_column() << endl;
    

    Application::Iterator newItr(newPos);
    return newItr;
}

/*
getting the position of the iterator
*/
Position Application::Iterator::get_pos() const
{
    return *(posPtr);
}

/*
checking whether the position of the state has reached the end. 
*/
bool Application::Iterator::at_end() const
{
    return ( *( this -> posPtr ) == finish );
} 

/*
go back to where it comes from
(according to the element fromDiretion)
HOWEVER, WE CAN'T CHANGE THE FROMDIRECTION OF ITS BACK PLACE
BECAUSE IT WOULD AFFECT THE NEXT BACKTRACK.
*/
void Application::Iterator::go_back()
{
    cout << "DEBUG: ENTER GO_BACK\n";
    switch( posPtr -> get_fromDirection() )
    {
        //from the northside
        case 0:
            *this = back_upward();
            break;
        //from the east
        case 1:
            *this = back_eastward();
            break;
        //from the south
        case 2:
            cout << "okay?\n";
            Application::Iterator anotherItr = back_downward();
            cout << "hi\n";
            cout << "DEBUG AFTER BACK_DOWNWARD: the position is "
                 << anotherItr.posPtr->get_row() << " " 
                 << anotherItr.posPtr->get_column() << endl;
            break;
        //from the west
        //case 3:
           // *this = back_westward();
            //break;
    };
}

/*destructor
needed because I used a new command 
to get the posPtr pointer  
*/
Application::Iterator::~Iterator()
{
    delete posPtr;
}
