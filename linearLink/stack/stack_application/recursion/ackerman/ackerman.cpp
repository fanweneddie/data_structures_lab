/* the function of ackerman
ackerman(m,n) = n+1                                    ( m ==0)
              = ackerman(m-1,1)                      ( m!=0 and n==0 )
              = ackerman(m-1,ackerman(m,n-1))        ( m!=0 and n!=0 )
*/


#include<iostream>
#include <stack>
using namespace std;
//recursion method 
int ackerman_re(int m,int n)
{
    if( m == 0)
        return n + 1;
    else
    {
        if(n == 0)
            return ackerman_re(m - 1, 1);
        else
            return ackerman_re(m - 1, ackerman_re(m, n - 1));
    }
}

void Print_stack(const stack<int>& otherStack)
{
    stack<int> tempStack = otherStack;
    while( !tempStack.empty())
    {
        cout << tempStack.top() << " ";
        tempStack.pop();
    }
    cout << endl;
}

// non-recursive version
//using the stack to analyze.
int ackerman_nre(int m,int n)
{
    stack<int> analysis;
    analysis.push(m);
    analysis.push(n);
    int tempM, tempN;
     Print_stack(analysis);
    //before the result is given, the stack analysis has more than one numbers in it.
    while( analysis.size() != 1 )
    {
        tempN = analysis.top();
        analysis.pop();
        tempM = analysis.top();
        analysis.pop();
        if(tempM == 0)
        {
            analysis.push(tempN + 1);
        }
        else if( tempN ==0 )
        {
            analysis.push(tempM - 1);
            analysis.push(1);
        }
        else
        {
            analysis.push(tempM - 1);
            analysis.push(tempM);
            analysis.push(tempN - 1);
        }
        Print_stack(analysis);
    }// while( analysis.size() != 1 )
    return analysis.top();
}

void test_re()
{
    int m, n,choice;
    int result;
    cout << "testing the recursive version of ackerman function.\n";
    while(1)
    {
        cout << "please input the value of m and n\n";
        cin >> m >> n;
        result = ackerman_re(m,n);
        cout << "ackerman(" << m << "," << n << ") is " << result << endl;
        cout << "enter 0 to quit.\n";
        cin >> choice;
        if (choice == 0)
            break;
    }
}

//please vamos!!!!!!
void test_nre()
{
    int m, n,choice;
    int result;
    cout << "testing the non recursive version of ackerman function.\n";
    while(1)
    {
        cout << "please input the value of m and n\n";
        cin >> m >> n;
        result = ackerman_nre(m,n);
        cout << "ackerman(" << m << "," << n << ") is " << result << endl;
        cout << "enter 0 to quit.\n";
        cin >> choice;
        if (choice == 0)
            break;
    }
}

int main()
{
   // test_re();
    test_nre();
    return 0;
}