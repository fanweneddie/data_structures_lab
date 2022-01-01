#include <iostream>
#include <ctime>
using namespace std;
const int SIZE = 8;
int state[SIZE][SIZE];

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
//dfs
void queen(int row,int &order)
{
    int column = 0;
    for (; column < SIZE;++column)
    {
        if( !is_attacked(row,column) )
        {
            state[row][column] = 1;
            if(row == SIZE -1)
            {
                print_state(order);
                ++order;
            }
            else
                queen(row + 1,order);
            state[row][column] = 0;
        }
    }
}

int main()
{
    for (int i = 0; i < SIZE;++i)
        for (int j = 0; j < SIZE;++j)
            state[i][j] = 0;
    int order = 1;
    clock_t startTime = clock();
    queen(0,order); 
    clock_t endTime = clock();
    cout << "the lasting time of recursive process is " 
        << endTime - startTime << " milliseconds"<< endl;
    return 0;
}