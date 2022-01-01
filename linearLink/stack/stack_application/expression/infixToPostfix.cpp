// transmitting the common infix expression 
// to the postfix expression ( reversed polish)
#include<iostream>
#include <stack>
#include <string>
using namespace std;

bool is_letter(const char& inputChar)
{
    return (inputChar >= 'A' && inputChar <= 'Z') 
        || (inputChar >= 'a' && inputChar <= 'z');
}

/* getting the priority of the operator
the priority of '+' and '-' is 1;
'*' and '/' is 2;
'(' is 3;
')' is 4;
default is 0;
*/
int optr_prty(const char& inputchar)
{
    switch(inputchar)
    {
        case '+' :
           // return 1;
        case '-' :
            return 1;
        case '*':
           // return 2;
        case '/':
            return 2;
        case '(':
           // return 3;
        case ')':
            return 3;
        default:
            return 0;
    }
}

/* transmitting the infix expression to the postfix expression
input: string infix that is a infix expression with letters operand and arithmetic operator
output: a string of a postfix expression (without bracket)
*/
string infix_to_postfix(const string & infix)
{
    stack<char> optrs;
    string postfix;
    auto itrInfix = infix.begin();
    //traversing the operand and operator in the infix expresison
    for (; itrInfix != infix.end();++itrInfix)
    {
        // if the element is an operand, we just need to output it in the postfix expression.
        if( is_letter( *itrInfix ) )
        {
            postfix += *itrInfix;
        }
        //the element is an operator
        else
        {
            //case1 : the operator is')'
            if( *itrInfix == ')')
            {
                //we need to pop out all the operators between '(' and ')'
                //and input them into the postfix expression.
                while( optrs.top() != '(' )
                {
                    postfix += optrs.top();
                    optrs.pop();
                }
                // we also need to pop the '('
                optrs.pop();
            }

            //case 2: the operator is not '('
            else
            {  
                // pop out the operators whose priority is bigger than
                // the current operator.( except '(' )
                // Also we should input those operators into the postfix expression.
                while( !optrs.empty()   && 
                (  optrs.top() != '(' &&
                optr_prty( optrs.top() ) >=  optr_prty(*itrInfix)  ) )
                {
                    postfix += optrs.top();
                    optrs.pop();
                }
                // don't forget to push the current operator into the optrs stack.
                optrs.push(*itrInfix);
            }//else of //case 2: the operator is not '('
        }//else of //the element is an operator
    }//for of //traversing the operand and operator in the infix expresison

    // after traversing all the elements in the infix expression, 
    //we should pop the operators in the optrs stack 
    // and input them into the postfix expression.
    while( !optrs.empty() )
    {
        postfix += optrs.top();
        optrs.pop();
    }
    return postfix;
}

//testing 
int main()
{
    string infixExp, postfixExp;
    while(1)
    {
        cout << "please input a string of infix expression. Enter q to quit.\n";
        cin >> infixExp;
        if(infixExp == "q")
            break;
        postfixExp = infix_to_postfix(infixExp);
        cout << "the postfix expression is \n"
             << postfixExp << endl;
    }
    return 0;
}