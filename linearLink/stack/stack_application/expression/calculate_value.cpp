//calculate the value of an (infix)expression that we input
#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <cmath>
using namespace std;

// checking whether the character is an operator.
bool IsOperator( char inputChar)
{
    switch(inputChar)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '(':
        case ')':
        case '#':
        case '@':// means --
            return true;
        default:
            return false;
    }
}

//if the char is an operator, we need to get its index in the 8*8 matrix
int find_optrIndex( char optr)
{
    switch(optr)
    {
        case '+':
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '^':
            return 4;
        case '(':
            return 5;
        case ')':
            return 6;
        case '#':
            return 7;
        default:
            break;
    }
    return 0;
}

//using a 8*8 matrix to compare the priority of the binary operator 
// at the top of the OPTR stack and the current operator.
int compare_priority(char a,char b)
{
    // 1 stands for > , 0 stands for = , -1 stands for <
    // adding the ^ operator at line and column 4
    // since the -- is a unary operator, we can set its priority as the highest
    // and consider it alone
    int cmpTable[8][8] = { {1, 1, -1, -1,-1, -1, 1, 1},
                          {1, 1, -1, -1, -1, -1, 1, 1},
                          {1, 1, 1, 1, -1, -1, 1, 1},
                          {1, 1, 1, 1, -1, -1, 1, 1},
                          {1, 1, 1, 1, 1, -1, 1, 1},
                          {-1, -1, -1, -1, -1, -1, 0, 0},
                          {1, 1, 1, 1, 1, 0, 1, 0},
                          {-1, -1, -1, -1,-1, -1, 0, 0} };
    return cmpTable[find_optrIndex(a)][find_optrIndex(b)];
}

//getting a number after the index from the expression
double get_num(string expression,int & startIndex)
{
    int i = startIndex, leng = expression.length();
    int resultInt = 0;
    double resultDec = 0, result = 0;
    // let result = resultInt + resultDec.
    bool flagOfInt = true;
    int pointPos = 0;
    // if flag == true, it is the integer part,
    // or it is the decimal part.
    for (; i < leng;++i)
    {
        //if now is searching the integal part of the number
        if( flagOfInt == true && expression[i] >= '0' && expression[i] <= '9')
        {
            resultInt *= 10;
            resultInt += expression[i] - '0';
        }
        // if now is searching the decimal part of the number
         else if( flagOfInt == false && expression[i] >= '0' && expression[i] <= '9')
        {
            resultDec *= 10;
            resultDec += expression[i] - '0';
        }
        // have searched the decimal point, change to increment the resultDec
        else if( flagOfInt == true && expression[i] == '.' )
        {
            flagOfInt = false;
            pointPos = i;
        }
        else
            break;
    }
    // we first get the amplified value of the decimal part of the result,
    //we need to return to its original value.
    for (int j = 1; j < i - pointPos;++j)
        resultDec /= 10;
    result = resultInt + resultDec;
    // we need to change the startindex (which is a reference argument) 
    // to serve for the next get_num search
    startIndex = i;
    return result;
}

//calculate the value by using the binary operator
double operate_bi(double operandA,double operandB,char optr)
{
    switch(optr)
    {
        case '+':
            return operandA + operandB;
        case '-':
            return operandA - operandB;
        case '*':
            return operandA * operandB;
        case '/':
            if(operandB == 0)
                throw "the denominator should not be 0.\n";
            else
                return operandA / operandB;
        case '^':
            return pow(operandA, operandB);
        default:
            break;
    }
    return 0;
}

// the core function to calculate the value of a infix expression
double calculate_infix(string expre)
{
    //the stack to store the operator
    stack<char> OPTR;
    OPTR.push('#');// in order to match the '#' at the end of the expression.
    //the stack to store operand
    stack<double> OPND;
    int index = 0;
    char optr;
    double opnda, opndb;
    //the condition that the calculating is still on.
    while(  expre[index] != '#' || OPTR.top() != '#'  )
    {
        //if the char is not an operator,
        // it must be a digit and we can extract the corresponding number
        // and push it into the OPND stack 
        if( !IsOperator(expre[index]) )
        {
            double tempoprand = get_num(expre, index);
            OPND.push( tempoprand );
            continue;
        }
        //consider the -- alone(we have replaced -- with @ before)
        //since '--' is a unary operator and it has the highest priority
        // once we meet it, we can get a number from the OPND and --it.
        if( expre[index] == '@')
        {
            opnda = OPND.top();
            OPND.pop();
            opnda--;
            OPND.push(opnda);
            ++index;//don't forget ,or it will fall into a forever loop.
            continue;
        }
        // the case that the current character is an operator
        //compare the priority between the current operator 
        //  and the operator at the top of the OPTR
        switch( compare_priority( OPTR.top(), expre[index]) )
        {
            // the priority : OPTR.top() < *itr
            // which means that we should consider the latter one, 
            //just push it intos the OPTR stack
            case -1:
                OPTR.push(expre[index]);
                ++index;
                break;

            // the priority: OPTR.top() = *itr
            // only the case of '(' and ')' 
            // we need to delete the bracket
            case 0:
                optr = OPTR.top();
                OPTR.pop();
                ++index;
                break;
            
            //the priority: OPTR.top() > current operator
            //we need to first consider the first one,
            // and pop the operands to get calculate
            case 1:
                optr = OPTR.top();
                opnda = OPND.top();
                OPND.pop();
                opndb = OPND.top();
                OPND.pop();
                OPTR.pop();
                //get the opndb opnda and optr from the stack and pop them out.
                double temp = operate_bi(opndb, opnda, optr); // calculate b op a
                OPND.push( temp );
            // pay attention , the operating sequence is reversed due to lifo
            // don't forget to convert from char to double.     
            break;
        }//switch
    }//while
    // finally the *itr and the OPTR.top() will both be '#'
    return OPND.top();
}

int main()
{
    string expression;
    while(1)
    {
        cout << "please input an arithmatic infix expression. enter quit to quit.\n";
        cin >> expression;
        //adding '#' as a ending sign
        if(expression == "quit")
            break;
        //add '#' to the end of the expression as an ending sign
        expression = expression + "#";

        //set @ as operator--
        //replace the -- with @ 
        int selfMinusPos = 0;
        while( expression.find("--",selfMinusPos) != expression.npos )
        {
            selfMinusPos = (int) expression.find("--", selfMinusPos);
            expression.replace(selfMinusPos, 2, "@");
        }
        //dealing with the negetive sign by simply adding 0 before it
        // the negetive sign '-' can only occur at the beginning of an expression
        // or right after the left bracket '('.
        int negSignPos = 0;
        if(expression[0] == '-')
        {
            expression.insert(0, "0");
        }
        while (expression.find("(-", negSignPos) != expression.npos)
        {
            negSignPos = (int) expression.find("(-", negSignPos);
            expression.insert(negSignPos+1,"0");
        }
        //attention: since we need a reference argument, we should pass a variable that is 0
        // not just only passing a constant 0.
        int index = 0;
        double result = get_num(expression, index);
        try
        {
            result = calculate_infix(expression);
            cout << "the result of this expression is " << result << endl;
        }
        // throwing an exception that the 0 becomes a dominator when dividing numbers.
        catch( const char *s)
        {
            cout << s << endl;
        }
    }//while(1)
    cout << "DONE!\n";
    return 0;
}