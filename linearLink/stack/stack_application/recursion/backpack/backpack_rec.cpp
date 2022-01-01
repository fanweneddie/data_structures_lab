#include <iostream>
using namespace std;
const int MAXSIZE = 10;
int state[MAXSIZE];
int weight[MAXSIZE];

void print_solution(int &count,const int &size)
{
    cout << "the " << count << "th solution: \n";
    for (int i = 0; i < size;++i)
    {
        if(state[i] == 1)
            cout << weight[i] << " ";
    }
    cout << endl;
}
//THE RECURSIVE FUNCTION FOR THE BACKPACK PROBLEM
void sol(int index,int leftWeight,int & count,const int & size)
{
    //the search has reached the end   
    if (index >= size)
        return;
    // search the circumstance including fetching the current stone.
    if(weight[index] <= leftWeight)
    {
        //mark that we will fetch this stone
        state[index] = 1;
        if (weight[index] == leftWeight)
        {
            print_solution(count,size);
            ++count;
        }
        //search for the stone at the next place.
        else
            sol(index + 1, leftWeight - weight[index], count,size);
        //resume the stone
        state[index] = 0;
    }
    //search the circumstance without fetching the current stone
    sol(index + 1, leftWeight, count, size);
} // since there are many repetition of calculating, the time is O(2^number);
//slow!!!!!

int main()
{
    for (int i = 0; i < MAXSIZE;++i)
        state[i] = 0;
    int capacity, num;
    cout << "please input the capacity of the backpack.\n";
    cin >> capacity;
    cout << "please input the number of stones.\n";
    cin >> num;
    cout << "please input the weight of those " << num << " stones.\n";
    for (int i = 0; i < num;++i)
        cin >> weight[i];
    int count = 1;
    sol(0, capacity, count, num);
    return 0;
} 
