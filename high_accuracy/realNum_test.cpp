#include "ioNum.cpp"
using namespace std;
int main()
{
    RealNumber rn1,rn2,rn3;
    cout << "please input a real number for rn1.\n";
    cin >> rn1;
    cout << "rn1 is " << rn1 << endl;
    cout << "please input a real number for rn2.\n";
    cin >> rn2;
    cout << "rn2 is " << rn2 << endl;
    /*
    rn3 = rn1 + rn2;
    cout << "the value of rn1 + rn2 is " << rn3 << endl;
    cout << "the int len of rn1 + rn2 is " << rn3.integerLen << endl;
    
    cout << "the value of rn1 - rn2 is \n";
    cout << rn1 - rn2 << endl;
    */
    rn3 = rn1 * rn2;
    cout <<  "the value of rn1*rn2 is " << rn3 << endl;
    return 0;
}