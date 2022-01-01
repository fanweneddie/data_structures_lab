#include "Position.h"
/*
Describe one position of a matrix or a grid;
*/
//fromDirection: 0:from up ;
// 1:from east ; 2: from south ; 3: from west

//initializing constructor
Position::Position(int Row , int Column,int FromDirection  )
{
    row = Row;
    column = Column;
    fromDirection = FromDirection;
}

//changing to the new position
void Position::set_position(int Row,int Column,int FromDirection )
{
    row = Row;
    column = Column;
    fromDirection = FromDirection;
}


//getting the protected value
int Position::get_row() const
{
    return row;
}

int Position::get_column() const
{
    return column;
}

int Position::get_fromDirection()const
{
    return fromDirection;
}

bool Position::operator==(const Position &newPositon) const
{
    return ( row == newPositon.get_row() 
            && column == newPositon.get_column() );
}
