#ifndef POLYNOMIAL
#define POLYNOMIAL
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;
struct Item 
{
    double coef;
    int exp;
    //in order to inplement quick sort,
    //-we need the double direction
    Item* next;
    Item *last;
};

//finding the index of of the base number *lowPtr
Item *get_index(Item *lowPtr, Item *highPtr);
// an auxiliary function to polish each item in a mathematical format.
string printItem(bool isFirst, double coef, int exp);

class Polynomial
{
    public:
        //in this case, I store the nothing in head.
        Item *head;
        //in order to make the quicksort quicker,
        // I set a tail ptr to avoid traversing the whole list.
        Item *tail;
        int itemNum;
        int maxExp;
    public:
        //default constructor
        Polynomial();
        void create_Polynomial();
        
        void quick_sort(Item *lowPtr, Item *highPtr);
        int get_itemNum() const { return itemNum; }
        int get_maxExp() const { return maxExp; }

        //friend istream &operator>>(istream &in, const Polynomial &pl);
        friend ostream &operator<<(ostream &out, const Polynomial &pl);
        Polynomial &operator=(const Polynomial &pl);
        Polynomial operator+( const Polynomial &anotherPoly);
        Polynomial operator-(const Polynomial &anotherPoly);
        Polynomial operator*(const Polynomial &pl);
        
        ~Polynomial()
        {
            Item* tempPtr = head;
            while( tempPtr->next != nullptr )
            {
                tempPtr = tempPtr->next;
                delete tempPtr->last;
            }
            delete tempPtr;
        }
};

#endif
