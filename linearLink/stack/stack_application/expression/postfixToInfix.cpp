//transmit the postfix( reverse polish ) expression
//to the infix expression.
#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct item
{
    string expr;
    int link_optr;
    // if the item is only an operand, link_optr = 0;
    // if the item is linked by + or -, link_optr = 1;
    // if the item is linked by * or /, link_optr = 2;
};

//judge whether the inputchar is a letter.
bool is_letter( const char & inputChar)
{
    return (inputChar >= 'A' && inputChar <= 'Z') 
    || (inputChar >= 'a' && inputChar <= 'z');
}

// transmitting the postfix expression to the infix expression
string postfix_to_infix(const string & postfix)
{
    stack<item> analysis;
    auto itr = postfix.begin();
    //traversing every optr and oprand of the postfix.
    for (; itr != postfix.end();++itr)
    {
        // case1: the char is an oprand
        // we push it into the stack and mark its link_optr as 0. 
        if( is_letter( *itr ) )
        {
            item newItem;
            newItem.expr = *itr;
            newItem.link_optr = 0;
            analysis.push( newItem );
        }
        // case 2: the char is an operator '+' or '-'
        // we pop the top two elements of the stack and use the operator to link them.
        else if( *itr == '+' || *itr == '-' )
        {
            item itemA,itemB;
            itemB = analysis.top();
            analysis.pop();
            itemA = analysis.top();
            analysis.pop();
            // if the linking operator of the top item is '+' or '-',
            // we should add bracket for this item.
            if( itemB.link_optr == 1 )
            {   
                itemB.expr  = '(' + itemB.expr + ')';
            }
            itemA.expr = itemA.expr + *itr + itemB.expr ;
            itemA.link_optr = 1;
            // don't forget to push the new result item into the stack.
            analysis.push(itemA);
        }//else if( *itr == '+' || *itr == '-' )

        //case 3: the char is an operator '+' or '-'
        else
        {
            item itemA,itemB;
            itemB = analysis.top();
            analysis.pop();
            itemA = analysis.top();
            analysis.pop();
            // Regarding the second top item.
            // if the linking operator of that item is '+' or '-',
            // add bracket.
            if( itemA.link_optr == 1 )
            {
                itemA.expr = '(' + itemA.expr + ')';
            }
            // Regarding the top item.
            // if the linking operator of that item is '+' or '-' or '*' or '/' ,
            // add bracket.
            if(itemB.link_optr > 0 )
            {
                itemB.expr = '(' + itemB.expr + ')';
            }
            itemA.expr = itemA.expr + *itr + itemB.expr;
            itemA.link_optr = 2;
            //don't forget to push the result into the stack.
            analysis.push(itemA);
        }//else
    }//for (; itr != postfix.end();++itr)
    return  analysis.top().expr;
}

void test()
{
    string postfix, infix;
    // attention: the operand in the postfix expression must be letters.
    cout << "please input a postfix expression.\n";
    cin >> postfix;
    infix = postfix_to_infix(postfix);
    cout << "the corresponding infix is " << infix << endl;
}

int main()
{
    test();
    return 0;
}
