#ifndef EXPRESSION
#define EXPRESSION
#include "myBiTree.h"
#include <sstream>

/* declaration for some recursive functions */
BiTNode *pre_order_create(string &inputString);
void inOrderTraverse_addBracket(BiTNode *T,int flagOfRoot);
void inOrderTraverse_addBracket_concise(BiTNode *T,bool flagOfAddBracket);
double calculate_value(BiTNode *T);

/* declaration for some trivial auxiliary functions  */
//returning the priority of a node
int operator_level(string s);

// using public succession of the binary tree ADT
class ExpreTree: public MyBiTree
{   
    protected:
    //the result of the expression ( supposed that the operands are all numbers)
        double value;

      public:
        //constructor
        ExpreTree( string &inputString)
        {
          root = pre_order_create(inputString);
        }
        //getting the infix expression
        void in_Order_Traverse() const  
        {
          int flagOfRoot = 0;
          inOrderTraverse_addBracket(root,flagOfRoot); 
        }
        //getting the expression with concise bracket(without redundency)
        void in_Order_Traverse_Concise() const
        {
            inOrderTraverse_addBracket_concise(root,false);
        }

        void compute_value()
        {
            value = calculate_value(root);
        }

        int get_value() const { return value; }
};

//input a prefix expression and create the expressionTree
//supposed that the prefix expression is valid 
//- and that the operators in the prefix expression are all binary.
// the seperation sign is the blank space. 
BiTNode *pre_order_create( string &inputString)
{
    BiTNode *tempNode = nullptr;
    //the traverse of the inputstring is over, tree is built.
    if(inputString == "")
      return nullptr;
    int sepeIndex = inputString.find(' ', 0);
    if(sepeIndex < 0)
    {
      sepeIndex = inputString.length();
    }
    //s is the content between the start and the seperation sign.
    string s = inputString.substr(0, sepeIndex);
    tempNode = new BiTNode;
    tempNode->data = s;
    // s is a number,it must be a leaf node
    if( operator_level(s) == 0 )
    {
      tempNode->lchild = nullptr;
      tempNode->rchild = nullptr;
    }
    // ch is an operator
    else 
    {
      //let inputSTring be the string cutting off the previous content.
      // if the previous content is the end , the new inputString is ""
      inputString = inputString.substr(sepeIndex + 1);
      tempNode->lchild = pre_order_create(inputString);
      //later,consider the right child in the same way.
      sepeIndex = inputString.find(' ', 0);
      if( sepeIndex < 0 )
        sepeIndex = inputString.length()-1;
      inputString = inputString.substr(sepeIndex + 1);
      tempNode->rchild = pre_order_create(inputString);
    }
    return tempNode;
}

//adding the bracket for each item in the infix expression
// for the items connected by the root operator, 
//it does not need to be added bracket. 
void inOrderTraverse_addBracket(BiTNode *T,int flagOfRoot)
{
    //flagOfRoot = 0: a root ; flagOfRoot > 0 :not a root.
    if(T)
    {
        // a non-root operator
        if( flagOfRoot > 0 && operator_level(T->data) )
            cout << "( ";
        inOrderTraverse_addBracket(T->lchild,flagOfRoot + 1);
        visit(T->data);
        inOrderTraverse_addBracket(T->rchild,flagOfRoot + 1);
        if(flagOfRoot > 0 && operator_level( T->data ) )
            cout << ") ";
    }
}

/*  only add the necessary bracket for the infix expression. */
// if flagOfAddBracket is true, the expression connected by the T optr is
//- required to add bracket.
// also ,we can figure out the flagofAddBracket for the next subExpression by 
//-comparing the priority.
void inOrderTraverse_addBracket_concise(BiTNode *T,bool flagOfAddBracket)
{
  // such as the case A--B--C
  if (T)
  {
    //consider for the A(left subexpression.)
    bool tempFlagOfAddBracket = false;
    //1. B is a number, don't add bracket for A
    if (operator_level(T->data) == 0 )
        tempFlagOfAddBracket = false;
    else if ( operator_level(T->data) > 0 )
    {
      //2. B is an optr but its priority <= A's priority(A is alos an optr)
      // don't add bracket for A
        if( operator_level(T->lchild->data) >= operator_level(T->data) )
             tempFlagOfAddBracket = false;
      // 3. B is an optr and A is a number, don't add bracket for A.
        else if( operator_level(T->lchild->data) == 0 )
            tempFlagOfAddBracket = false;
      //4. B is optr , A is optr and priority : B > A
      // add bracket for AA.
        else
          tempFlagOfAddBracket = true;
    } 
    // 1,2,3 are all the cases for add bracket for left subexpression,
    // for the rest, we need to add bracket.  
    else
    {
        tempFlagOfAddBracket = true;
    }

    if( flagOfAddBracket)
        cout << "( ";
    inOrderTraverse_addBracket_concise(T->lchild,tempFlagOfAddBracket);
    visit(T->data);
    //considering the right subexpression,similar to the left subexpression
    if (operator_level(T->data) == 0 )
        tempFlagOfAddBracket = false;
    else if ( operator_level(T->data) > 0 )
    {
      // the only difference: B and C are both optr and
      // -we DON'T add bracket only when the priority: C > B
      // if priority: C = B, we had better add bracket 
      //- because it shows the computing sequence.
        if( operator_level(T->rchild->data) > operator_level(T->data) )
             tempFlagOfAddBracket = false;
        else if(operator_level(T->rchild->data) == 0)
            tempFlagOfAddBracket = false;
        else
            tempFlagOfAddBracket = true;
    }   
    else
    {
        tempFlagOfAddBracket = true;
    }

    inOrderTraverse_addBracket_concise(T->rchild,tempFlagOfAddBracket);

    if(flagOfAddBracket == true)
      cout << ") ";
  }
}

//calculate the value of that expression.
//using the tree and the recursion.(from root to leaves)
double calculate_value(BiTNode *T)
{
    if(T)
    {
        if( T->data == "+" )
          return calculate_value(T->lchild) + calculate_value(T->rchild);
        else if ( T->data == "-")
          return calculate_value(T->lchild) - calculate_value(T->rchild);
        else if( T->data == "*")
          return calculate_value(T->lchild) * calculate_value(T->rchild);
        else if( T->data == "/")
          return calculate_value(T->lchild) / calculate_value(T->rchild);
        // the data is a number, so we need to transform it from the string to double.
        else
        {
            double number;
            stringstream ss;
            ss << T->data;
            ss >> number;
            return number;
        }
    }//if(T)
    else
      return 0;
}

//returning the priority of a node :
// if '*' or '/' : return 2
// if '+' or '-' : return 1
// if it is just a operand, return 0
int operator_level(string s)
{
    if( s == "+" || s == "-")
      return 1;
    else if( s == "*" || s == "/")
      return 2;
    else
      return 0;
};

#endif