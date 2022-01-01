#ifndef POSITION
#define POSITION
/*
Describe one position of the matrix or a grid.
*/
class Position
{
    protected:
        int row;
        int column;
        int fromDirection;
        //fromdDirection:   0: from up ; 
        //1:from east ; 2:from down ; 3:from west
        //the default fromDirection is from down
    public:
        //initializing constructor
        Position(int Row = 0, int Column = 0,int FromDirection = 2);
        //changing to the new position
        void set_position(int Row, int Column, int FromDirection);
        //getting the protected value
        int get_row() const;
        int get_column() const;
        int get_fromDirection() const;
        bool operator==(const Position &newPositon) const;
};

#endif