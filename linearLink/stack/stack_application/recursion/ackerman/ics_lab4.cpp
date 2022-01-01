#include <iostream>
using namespace std;
#include <stack>
int i = 0;
int func_rec( int n, int a,int b,int c,int d,int e,int f)
{
    int num;
    cout << i << ": please input a num when calculating func_rec(" << n << "," << a << "," << b << ","
     << c << "," << d << "," << e << "," << f << ").\n";
    //cin >> num;
    ++i;
    num = 1;
    int t = num + a + b + c + d + e + f;
    if( n > 1)
    {
        int x = func_rec(n - 1, a, b, c, d, e, f);
        int y = func_rec(n - 2, a, b, c, d, e, f);
        return x + y + t - 1;
    }
    else
        return t;
}


int func_nonrec( int n, int a,int b,int c,int d,int e,int f)
{
    stack<int> S1,S2;
    int num;
    cout << "please input a num when calculating func_nonrec(" << n << "," << a << "," << b << ","
     << c << "," << d << "," << e << "," << f << ").\n";
    //cin >> num;
    num = 1;
    S1.push(n);
    S2.push(num);
    int sum = 0;
    int topNum = 0;
    int topValue = 0;
    while( !S1.empty() )
    {
        topNum = S1.top();
        //cout << "Debug01: topNum = " << topNum << endl;
        S1.pop();
        if( topNum <= 1 )
        {
            topValue = S2.top();
            S2.pop();
            sum += topValue;
        }
        else
        {
            //for p-1
            cout << "please input a num when calculating func_non_rec(" << topNum - 1 << "," << a << "," << b << ","
            << c << "," << d << "," << e << "," << f << ").\n";
            cin >> num;
            S1.push(topNum - 1);
            S2.push(num);
            //for p-2
             cout << "please input a num when calculating func_non_rec(" << topNum - 2 << "," << a << "," << b << ","
            << c << "," << d << "," << e << "," << f << ").\n";
            cin >> num;
            S1.push(topNum - 2);
            S2.push(num);
        }
    }//while( !S1.empty() )
    while( !S2.empty() )
    {
        topValue = S2.top();
        S2.pop();
        sum += topValue - 1;
    }
    return sum;
}

int main()
{
    int res =  func_rec(9, 0, 0, 0, 0, 0, 0);
    //int res = func_nonrec(4, 0, 0, 0, 0, 0, 0);
    cout << "the result is \n";
    cout << res << endl;
    return 0;
}