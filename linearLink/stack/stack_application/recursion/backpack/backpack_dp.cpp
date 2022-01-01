#include <iostream>
using namespace std;
const int MAXSIZE = 10;
//result[i][j] means the local best result of the prior i stones
//when the current capacity is j
int result[MAXSIZE][MAXSIZE];
//store the weight and value of each stone
int weight[MAXSIZE];
int value[MAXSIZE];

//using non resursive way to find the best result
void dynamic_find_max(int number,int capacity)
{
    //traversing all stones and all capacity.(bottom up)
    for (int i = 1; i <= number;++i)
    {
        for (int j = 1; j <= capacity;++j)
        {
            // the current stone is too big,skip it
            if(j < weight[i])
            {
                result[i][j] = result[i - 1][j];
            }
            // the current stone is not too big, compare which is better
            // loading it or not loading it.
            else
            {
                if( result[i - 1][j] > result[i - 1][j - weight[i]] + value[i] )
                {
                    // not loading it is better
                    result[i][j] = result[i - 1][j];
                }
                else
                {
                    //loading it is better
                    result[i][j] = result[i - 1][j - weight[i]] + value[i];
                }
            }
        }
    }
    cout << "the best result is " << result[number][capacity] << endl;
    for (int i = 0; i <= number;++i)
    {
        for (int j = 0; j <= capacity;++j)
            cout << result[i][j] << " ";
        cout << endl;
    }
} // the Time is O(number*capacity)

//after finding the best result,
//we need to find the composition of that result
void find_what(int number, int capacity)
{
    //using array item to set the mark which represent whether or not load that stone.
    int item[number + 1];
    for (int i0 = 0; i0 <= number;++i0)
        item[i0] = 0;
    int i = number, j = capacity;
    // use iteration to search the picked stones from the last one to the first one.
    while(i > 0)
    {
        //case 1: not load that stone
        if( result[i][j] == result[i-1][j] )
            item[i] = 0;
        //case 2: load that stone
        else if( j > weight[i] && result[i][j] == result[i-1][j - weight[i]] + value[i] )
        {
            //set the mark and decrease the current capacity 
            item[i] = 1;
            j = j - weight[i];
        }
        --i;
    }//while(i > 0)

    cout << "the stone being fetched: ";
    for (int k = 1; k <= number;++k)
        if(item[k] == 1)
            cout << k << " ";
    cout << endl;
}

// the testing data: num = 4,capa = 8
//order     1   2   3   4
//weight    2   3   4   5
//value     3   4   5   6
int main()
{
    int num,capa;
    cout << "please input the capacity of the bag and the number of the stone.\n";
    cin >> capa >> num;
    cout << "please input the weight and value of those " << num << " stones.\n";
    for (int i = 1; i <= num;++i)
    {
        cin >> weight[i] >> value[i];
    }
    //remember to initialize the result array( reset the 0th row and 0th column as 0)
    for (int i = 0; i <= num;++i)
    {
        result[0][i] = 0;
        result[i][0] = 0;
    }
    dynamic_find_max(num, capa);
    find_what(num, capa);
    return 0;
}

