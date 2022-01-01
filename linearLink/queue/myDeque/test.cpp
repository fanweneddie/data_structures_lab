#include <iostream>
using namespace std;

int main()
{
    int a[4] = {0, 1,2,3};
    //sint b[2] = {2, 3};
    int *p = a;
    p += 2;
    int *q = a;
    if(q<p-1)
    {
        cout << "yes\n";
    }

}




/*
int main()
{
    int a[2] = {0, 1};
    int b[2] = {2, 3};
    int *p[2];
    int **pp = p;
    *pp = a;
    *(pp + 1) = b;

    cout << "are you okay now?\n";
    for (int i = 0; i < 1;i++)
    {
            cout << *(*pp) << endl;
            pp = pp + 1;
    }
    cout << "deleting pp\n";
    delete pp;
    cout << "later, the pp: ";
    cout << "DONE!!!\n";
    return 0;
    
}
*/

/*
#include <string.h>
int main( )
{
    int a[4];
    memset(a, 2, 4*sizeof(int));
   
    int *p = a;
    int *q = a + 3;
    while( p <= q )
    {
        cout << *p<< endl;
        p++;
    }
    cout << a[0] << endl;
    return 0;
}
*/