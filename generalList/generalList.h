#ifndef GENERALLIST
#define GENERALLIST
#include <string>
#include <iostream>
#include <stack>
using namespace std;
// generally, there are three types of node.
enum Type
{
    HEAD,
    VALUE,
    SUB
};

struct GeneralNode
{
    Type type;
    GeneralNode * next;
    union
    {
        char value;
        GeneralNode *subLink;
    };
//constructor for the node.
    GeneralNode( Type ty, char vl = '\0') : type(ty), next(nullptr), value(vl) 
    {
        if( ty == SUB )
        {
            subLink = nullptr;
        }
    }
};

class GeneralList
{
    private:
        GeneralNode *head;
    public:
        GeneralList();
        GeneralList(  string & inputStr );
        friend ostream &operator<<(ostream &out, const GeneralList &gl);
        int get_amount() const;
        int get_depth() const;
        GeneralList &operator=(const GeneralList &gl);
        //~GeneralList();
};

GeneralList:: GeneralList()
{
    head = new GeneralNode(HEAD, '\0');
}

string delete_bracket(string s, int iLeft)
{
    stack<char> bracketStore;
    bracketStore.push('(');
    int len = s.length();
    for (int i = iLeft + 1; i < len;++i)
    {
        if( s[i] == '(')
        {
            bracketStore.push('(');
        }
        else if( s[i] == ')')
        {
            bracketStore.pop();
            if( bracketStore.empty() )
            {
                return s.substr(i + 1);
            }
        }//else if
    }//for
    return s;
}

GeneralNode* create_list( string inputStr)
{
    GeneralNode* head1 = new GeneralNode(HEAD, '\0');
    GeneralNode *current = head1;
    int len = inputStr.length(), i = 0;
    for (i = 0;i < len; ++ i )
    {
        if( inputStr.length() == 0)
        {
            return head1;
        }
        if( ( inputStr[i] >= 'a' && inputStr[i] <= 'z') || ( inputStr[i] >= 'A' && inputStr[i] <= 'Z') )
        {
            current->next = new GeneralNode(VALUE, inputStr[i]);
            current = current->next;
        }

        else if ( inputStr[i] == '(' )
        {
            current->next = new GeneralNode(SUB);
            current = current->next;
            string newsubstr = inputStr.substr(i + 1);
            current->subLink = create_list( newsubstr );
            inputStr = delete_bracket(inputStr, i);
            //really important to change the i as -1.
            // to make it turn 0 in the next step of the loop.
            i = -1;
        }
        else if( inputStr[i] == ')')
        {
            return head1;
        }
    }
    // keep safe.
    return head1;
}

GeneralList::GeneralList( string & inputStr)
{
    inputStr = inputStr.substr(1, inputStr.length() - 2);
    head = create_list(inputStr);
}

string printList(GeneralNode *head1)
{
    string outputStr;
    if( head1 == nullptr)
    {
        outputStr = "empty list.\n";
        return outputStr; 
    }

    GeneralNode *current = head1;
    while(current != nullptr)
    {
        if(current -> type == HEAD )
        {
            outputStr += "(";
        }
        else if (current -> type == VALUE )
        {
            outputStr += current->value;
            if(current -> next != nullptr)
            {
                outputStr += ",";
            }
        }
        else if(current -> type == SUB )
        {
            outputStr += printList(current->subLink);
            if(current -> next != nullptr)
           {
                outputStr += ",";
           }
        }
        current = current->next;
    }
    outputStr += ")";
    return outputStr;
}

ostream &operator <<(ostream & out, const GeneralList &gl)
{
    out << printList(gl.head);
    return out;
}

/*
checking whether the brackets in the input expression is valid
#############################################################3
*/
bool match(const char & charA, const char& charB)
{
    return (charA == '(' && charB == ')') ||
           (charA == '[' && charB == ']') ||
           (charA == '{' && charB == '}');
}

int bracket_type(const char& charA)
{
    //left bracket
    if( charA == '(' || charA == '[' || charA == '{' )
        return 1;
    //right bracket
    if( charA == ')' || charA == ']' || charA == '}' )
        return 2;
    //other char
    else
        return 0;
}
bool check_bracket( string expression)
{
    stack<char> bracketCheck;
    bracketCheck.push('#');
    for( string::iterator itr = expression.begin();
            itr != expression.end();++itr )
    {
        // *itr is left bracket,push it into the stack
        if( bracket_type(*itr) == 1 )
        {
            bracketCheck.push(*itr);
        }
        else 
        {
            //*itr is right bracket
            if( bracket_type(*itr) == 2 )
            {
                // if match, pop the corresponding left bracket.
                if( match(bracketCheck.top(),*itr) )
                    bracketCheck.pop();
                else // no match, so the expression is illegal.
                {
                    bracketCheck.push(*itr);
                    break;
                }
            }
        }
    }

    if(bracketCheck.top() == '#')
        return true;
    else
        return false;
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&7

#endif