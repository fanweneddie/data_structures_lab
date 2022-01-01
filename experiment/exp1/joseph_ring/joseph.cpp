#include <iostream>
#include <fstream>
#include "circularLink.h"
using namespace std;

/*simulating the process of the joseph ring
input: the original value of m, a single-direction circular link.
output: printing the player who is out in each round 
        and showing the winner at last.
*/
void joseph_simulation(int originM,CircularLink<int> josephRing )
{
    ofstream mycout("tempResult.txt");
    int m = originM;
    int outOrder = 0;
    Node<int> *ptr = josephRing.get_head()->next;
    // more than 1 player, the game is still on.
    while( josephRing.get_size() > 1 )
    {
        //using mod to let m in the range of (1,size] 
        // in order to reduce the repetition in the circulation.
        if( m % josephRing.get_size() != 0 )
            m = m % josephRing.get_size();
        else
            m = josephRing.get_size();

        // traverse the players in each round
        for (int i = 1; i < m;++i)
        {
            ptr = ptr->next;
            //skip the head of the circularLink.
            if( ptr == josephRing.get_head() )
            {
                ptr = ptr->next;
            }
        }
        // record the order and the code of the player who is out in the current round.
        m = ptr->data2;
        outOrder = ptr->data1;
        cout << outOrder << " is out.\n";
        mycout << outOrder << " is out.\n";
        // use a tempPtr to temporarily store the node to be erased later.
        Node<int> *tempPtr = ptr;
        //skip the head of the circularLink.
        do
        {
            ptr = ptr->next;
        } while (ptr == josephRing.get_head());
        josephRing.erase(tempPtr);
        
        // adjust m again to reduce repetition.
        if( m % josephRing.get_size() != 0 )
            m = m % josephRing.get_size();
        else
            m = josephRing.get_size();
    }
    cout << "the winner is " << josephRing.get_head()->next->data1 << endl;
    mycout << "the winner is " << josephRing.get_head()->next->data1 << endl;
    mycout.close();
}

/* pay attention: when using cmd to input the argument.
    1. the arguments are string.
    2.the first argument is the name of the cpp file.
*/
// the argument from the cmd: 
// m represents the original code.
// n represents the amount of people
// n - numbers representing the code. 
int main(int argc, char** argv)
{
    CircularLink<int> josephRing;
    int n  = atoi( argv[1] );
    int m = atoi(argv[2]);
    // constructing a circular link to simulate joseph ring.
    try
    {
        for (int i = 0; i < n;++i)
        {
            cout << "the argument is " << atoi(argv[i + 3]) << endl;
            //throw an exception when the amount of argument is not enough.
            if( atoi(argv[i + 3]) == 0 )
            {
                throw "the amount of arguments is not enough.\n";
            }
            josephRing.push_back( i+1, atoi(argv[i + 3]) );
        }
    }
    catch( const char * s)
    {
        cout << "EXCEPTION THROWN: \n";
        cout << s;
        exit(0);
    }
    try
    {
        joseph_simulation(m, josephRing);
    }
    catch( const char * s)
    {
        cout << "EXCEPTION THROWN: \n";
        cout << s;
        exit(0);
    }
    cout << "DONE!!!\n";
    return 0;
}
// the testing cmd input is  7 20 3 1 7 2 4 8 4
