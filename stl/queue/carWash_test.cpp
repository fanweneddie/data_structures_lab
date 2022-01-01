#include "carWash.cpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    const string CLOSE_WINDOW_PROMPT 
        = "PRESS ANY KEY TO CLOSE THE WINDOW.";

    CarWash carwash;

    carwash.stimulate();
    carwash.print_result();
    cout << CLOSE_WINDOW_PROMPT << endl;
    cin.get();
    return 0;
}