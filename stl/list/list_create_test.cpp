#include<stdio.h>
#include<iostream>
#include<list>
#include<string>
#include<algorithm>
using namespace std;

 

void PrintIt(string& StringToPoint)
{
cout << StringToPoint << endl;
}

int main()
{

list<string> test;

list<string>::iterator testiterator;

test.push_back("no");
test.push_back("march");
test.push_front("ok");
test.push_front("loleina");
test.push_front("begin");
test.push_back("end");

 

for (testiterator = test.begin(); testiterator != test.end(); ++testiterator)
{
cout << *testiterator << endl;
}
cout << "-------------" << endl;


for_each(test.begin(), test.end(), PrintIt);
cout << "-------------" << endl;

system("PAUSE");
return 0;
}
