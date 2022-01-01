#include <iostream>
#include <ctime>
using namespace std;
const int SIZE = 8;
int state[SIZE][SIZE];
int method[SIZE + 1];
int max(int num1,int num2,int num3,int num4)
{
    int temp1 = num1 > num2 ? num1 : num2;
    int temp2 = num3 > num4 ? num3 : num4;
    return temp1 > temp2 ? temp1 : temp2;
}

bool is_valid(int i,int j)
{
    if (i >= 0 && i < SIZE && j >= 0 && j < SIZE)
        return true;
    else
        return false;
}

bool is_attacked(int row,int column)
{
    for (int i = 0; i < SIZE;++i)
        if( state[i][column] == 1)
            return true;
    
     for (int j = 0; j < SIZE;++j)
        if( state[row][j] == 1)
            return true;

    int temp = max(row, column, SIZE - row, SIZE - column);
    for (int i = 1; i <= temp;++i)
    {
        if( is_valid(row + i,column + i) )
            if(state[row + i][column + i] == 1)
                return true;
         if( is_valid(row + i,column - i) )
            if(state[row + i][column - i] == 1)
                return true;
         if( is_valid(row - i,column + i) )
            if(state[row - i][column + i] == 1)
                return true;
         if( is_valid(row - i,column - i) )
            if(state[row - i][column - i] == 1)
                return true;
    }//for
    return false;
}

//output a solution of the chess board if that is valid
//use '#' to represent blank space, 'Q' to represent QUEUE
//it will tell the order of this sulotion.
void print_state(int order)
{
    cout << "the " << order << "th circumstance: \n";
    for (int i = 0; i < SIZE;++i)
    {
        for (int j = 0; j < SIZE;++j)
        {
            if(state[i][j] == 0)
                cout << "#";
            else
                cout << "Q";
        }
        cout << endl;
    }
}

//finding the solution in a non recursive way
void find_queen()
{
    int order = 1,top = 1;
    method[1] = 0;
    while(top > 0)
    {
        //putting a queen next to the current place.
        ++method[top];
        while(method[top] <= SIZE && is_attacked(top-1,method[top] -1) )
        {
            ++method[top];
        }
        state[top - 1][method[top] - 1] = 1;
        // the place of this queen is valid
        if(method[top] <= SIZE)
        {
            //the last row is reached
            if(top == SIZE)
            {
                print_state(order);
                ++order;
                state[top - 1][method[top] - 1] = 0;
                continue;
            }
            //go to search the solution of the next row
            else
            {
                ++top;
                method[top] = 0;
            }
        }
        // the place of this queen is not valid, backtrack.
        else
        {
            state[top - 1][method[top] - 1] = 0;
            --top;
            state[top - 1][method[top] - 1] = 0;
        }
    }//while top > 0
}

//using clock() to count the lasting time of execution
int main()
{
    for (int i = 0; i < SIZE;++i)
        for (int j = 0; j < SIZE;++j)
            state[i][j] = 0;
    clock_t startTime = clock();
    find_queen();
    clock_t endTime = clock();
    cout << "the lasting time of non recursive process is " 
        << endTime - startTime << " milliseconds"<< endl;
    return 0;
}