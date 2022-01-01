#include "polynomial.cpp"

void test()
{
    Polynomial p1,p2,p3;
    p1.create_Polynomial();
    cout << "now let's print the polynomial p1\n" << p1 << endl;
    p2.create_Polynomial();
    cout << "now let's print the polynomial p2\n" << p2 << endl;
    p3 = p1 + p2;
    cout << "now let's print the polynomial p1+p2\n" << p3 << endl;
    p3 = p1 - p2;
    cout << "now let's print the polynomial p1-p2\n" << p3 << endl;
    p3 = p1 * p2;
    cout << "now let's print the polynomial p1*p2\n" << p3 << endl;
    cout << "done!\n";
}

int main()
{
    test();
}