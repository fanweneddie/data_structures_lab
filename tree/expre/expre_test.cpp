#include "expression.h"

int main()
{
    string input;
    //input = "- 20 + 11 13";
    cout << "please input a string.\n";
    getline(cin, input);
    cout << "the inputString is " << input << endl;
    ExpreTree expT(input);
    cout << "finish constructing.\n";
    cout << "now getting the prefix expression.\n";
    expT.pre_Order_Traverse();
    cout << "\nnow getting the infix expression.\n";
    expT.in_Order_Traverse();
    cout << "\nnow getting the postfix expression.\n";
    expT.post_Order_Traverse();
    expT.compute_value();
    cout << "\nthe value of the expression is " << expT.get_value() << endl;
    cout << "now getting the infix expression with concise brackets.\n";
    expT.in_Order_Traverse_Concise();
    return 0;
    
}   