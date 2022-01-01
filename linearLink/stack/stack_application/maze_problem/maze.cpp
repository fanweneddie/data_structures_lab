#include <iostream>
#include <stack>
using namespace std;

class position
{
    public:
        int x;
        int y;
        int step;
        int dir; // 1: east , 2: south , 3:west , 4:north 
        position()
        {
            x = 0;
            y = 0;
            step = 1;
            dir = 1;
        }
        position(int inputx, int inputy, int inputStep ,int inputDir = 1)
        {
            x = inputx;
            y = inputy;
            dir = inputDir;
            step = inputStep;
        }
        position & operator = (const position& otherPos)
        {
            if( this != &otherPos)
            {
                x = otherPos.x;
                y = otherPos.y;
                step = otherPos.step;
                dir = otherPos.dir;
            }
            return *this;
        }

        bool operator == (const position & otherPos)
        {
            if( x == otherPos.x && y == otherPos.y )
                return true;
            else
                return false;
        }

        position next_position()
        {
            position nextPos;
            switch( dir )
            {
                case 1:  
                    nextPos.x = x;
                    nextPos.y = y + 1;
                    break;
                case 2:
                    nextPos.x = x + 1;
                    nextPos.y = y;
                    break;
                case 3:
                    nextPos.x = x;
                    nextPos.y = y -1;
                    break;
                case 4:
                    nextPos.x = x -1;
                    nextPos.y = y;
            }
            nextPos.step = step +1;
            nextPos.dir = 1;
            return nextPos;
        }
};

// 0 means the block and 1 means the path that has never been stepped.
// 2 means the path that has been searched. -1 means that the path can not lead to the end.
int maze[5][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0},
    {0, 1, 0, 1, 1, 0},
    {0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0}};

// only the place marked with 1 is accessible.
bool is_accessible(position Pos)
{
    if( maze[Pos.x][Pos.y] == 1)
        return true;
    else
        return false;
}


//dfs with the iteration version.
bool find_path( position start, position end)
{
    stack<position> Path;
    int curStep = 1;
    position curPos = start;
    do
    {
        if( is_accessible(curPos) )
        {
            // mark the footprint showing that this place has been searched.
            maze[curPos.x][curPos.y] = 2;
            curPos.dir = 1;
            curPos.step = curStep;
            //add this place as a part of the path.
            Path.push(curPos);
            // reaching the end of the maze.
            if(curPos == end)
            {
                //print the steps and the path.
                cout << "the total steps are " << curPos.step << endl;
                while( !Path.empty())
                {
                    cout << "the path include ( " << Path.top().x << " , " << Path.top().y << " )  <-- \n";
                    Path.pop();
                }
                return true;
            }
            // set the next position to be on the eastern side of the current place. 
            curPos = curPos.next_position();
            ++curStep;
        }
        // the curPos is not accessible.
        else
        {
            if( !Path.empty() )
            {
                curPos = Path.top();
                Path.pop();
                //firstly, we can pop the curPos out of the stack,
                // but we still need to trace this position, for we need to search its other direction.
                while( curPos.dir == 4 && !Path.empty() ) // no orient else to search, give it up.
                {
                    maze[curPos.x][curPos.y] = -1;
                    curPos = Path.top();
                    Path.pop();
                }

                // search the other direction
                if( curPos.dir < 4)
                {
                    ++curPos.dir;
                    Path.push(curPos);
                    curPos = curPos.next_position();
                }
            }
        }
    } while (!Path.empty());
    return false;
}


int main()
{
    position startPos(1, 1, 1), endPos(4, 4, 1);
    bool result = find_path(startPos, endPos);
    if(result)
        cout << "having found the right path.\n";
    else
        cout << "have not found the right path/\n";
    return 0;
}