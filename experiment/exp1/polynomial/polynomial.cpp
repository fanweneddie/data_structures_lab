#include "polynomial.h"
#include <sstream>
using std::stringstream;
//default constructor
Polynomial::Polynomial()
{
    head = new Item;
    tail = new Item;
    itemNum = 0;
    maxExp = -1;
    
    head->coef = 0;
    head->exp = -1;
    tail->coef = 0;
    tail->exp = -1;

    head->next = tail;
    head->last = nullptr;
    tail->last = head;
    tail->next = nullptr;
}

/* Ptr1 is at the next side of Ptr2 logically
(Ptr1 is bigger than Ptr2 ,to be brief)*/
// since it is the comparision between two Ptr,
// I don't really want to overload a operator again.
bool is_next(Item* Ptr1, Item*Ptr2)
{
    bool Ptr1IsBigger = false;
    if(Ptr2 != Ptr1)
    {
        while(Ptr2 != nullptr && !Ptr1IsBigger )
        {
            if(Ptr2 == Ptr1)
                Ptr1IsBigger = true;
            Ptr2 = Ptr2->next;
        }
    }

    return Ptr1IsBigger;
}

/* Ptr1 is at the prior side of Ptr2 logically
(Ptr1 is smaller than Ptr2 ,to be brief)*/
bool is_prior(Item* Ptr1, Item*Ptr2)
{
    bool Ptr1IsSmaller = false;
    if(Ptr1 != Ptr2)
    {
        while(Ptr1 != nullptr && !Ptr1IsSmaller )
        {
            if(Ptr1 == Ptr2)
                Ptr1IsSmaller = true;
            Ptr1 = Ptr1->next;
        }
    }

    return Ptr1IsSmaller;
}

Item *get_index( Item* lowPtr, Item *highPtr )
{
    //find the base number
    int tmpExp = lowPtr->exp;
    double tmpCoef = lowPtr->coef;
    //a while loop to find the right index
    while( is_next(highPtr,lowPtr) )
    {
        // based on the hignPtr, keep traversing to the left
        // - if the *highPtr >= the base number 
        while( is_next(highPtr,lowPtr) && highPtr->exp >= tmpExp)
            highPtr = highPtr->last;

        //the first highPtr from the right that doesn't satisfy the requirement
        //we can assign its value to lowPtr;
        lowPtr->exp = highPtr->exp;
        lowPtr->coef = highPtr->coef;
        //then we can base on the lowPtr. and so and so forth.
        while( is_next(highPtr,lowPtr) && lowPtr->exp <= tmpExp )
            lowPtr = lowPtr->next;
        //the first lowPtr from the left that doesn't satisfy the requirement
        //we can assign its value to highPtr;
        highPtr->exp = lowPtr->exp;
        highPtr->coef = lowPtr->coef;   
    }
    //
    lowPtr->exp = tmpExp;
    lowPtr->coef = tmpCoef;
    
    return lowPtr;
}


void Polynomial::quick_sort( Item* lowPtr, Item *highPtr )
{
    Item *indexPtr = nullptr;
    //IF highPtr is at the next side of lowPtr(highPtr is bigger)
    if( is_next(highPtr,lowPtr) )
    {
        indexPtr = get_index( lowPtr, highPtr);
        quick_sort(head->next,indexPtr ->last);
        quick_sort( indexPtr->next, highPtr);
    }
}


void Polynomial::create_Polynomial()
{
    int inputItemNum;
    cout << "please input the item number of polynomial.\n";
    cin >> inputItemNum;
    int inputExp;
    double inputCoef;
    Item *tempPtr1 = head,*tempPtr2;
    //input the items and prolong the link.
    for (int i = 1; i <= inputItemNum;++i)
    {
        cout << "please input the coefficient.\n";
        cin >> inputCoef;
        cout << "please input the exponent.\n";
        cin >> inputExp;
        // if the inputcoef is 0 ,then we don't need to record that Item.
        if(inputCoef != 0)
        {
            tempPtr2 = new Item;
            tempPtr2->exp = inputExp;
            tempPtr2->coef = inputCoef;
            tempPtr2->next = tail;
            tail->last = tempPtr2;
            tempPtr2->last = tempPtr1;
            tempPtr1->next = tempPtr2;
            tempPtr1 = tempPtr2;
            ++itemNum;
        }
    }
    //then,we need to sort this link.
    //I use the quick sort, whose worstTime is nlogn.
    Item *temp = head;
    while(temp->next != tail)
    {
        temp = temp->next;
    }
    //sorting the items by the exponent with an ascending order.
    quick_sort(head->next, tail->last);

    //another problem: we need to merge the items that has the same exponent.
    Item *ptrFirst = head->next,
         *ptrLast = head->next->next;
    //if the polynomial has more than 2 items.
    if(ptrFirst != tail && ptrLast != tail )
    {
        while(ptrLast != tail)
        {
            //looking for two consecutive nodes with the same exponent
            while( ptrFirst->exp != ptrLast->exp && ptrLast  != tail )
            {
                ptrLast = ptrLast->next;
                ptrFirst = ptrFirst->next;   
            }

            //after traversing the link, there is no repetition of the exponent.
            if(ptrLast == tail )
                break;
            //finding the repetition of the exponent.
            else
            {
                //first add up the coefficient in the items with the same exponent.
                ptrFirst->coef += ptrLast->coef;
                --itemNum;
                //since the exp of tail node is -1, we don't need to consider the tail 
                while(ptrLast->next->exp == ptrFirst->exp)
                {    
                    //continue adding up the coefficient in the items with the same exponent.
                    ptrLast = ptrLast->next;
                    ptrFirst->coef += ptrLast->coef;
                    --itemNum;
                }
                ptrLast = ptrLast->next;
                
                //if the new coefficient != 0
                if(ptrFirst->coef != 0)
                {
                    //delete all the nodes beween the ptrFirst and ptrLast
                    //excluding both bound.
                    Item *deletePtr = ptrFirst->next;
                    while(deletePtr->next!=ptrLast)
                    {
                        deletePtr = deletePtr->next;
                        delete deletePtr->last;
                    }
                    delete deletePtr;
                }

                // if the new coefficient ==0, we should delete all the nodes 
                //beween the ptrFirst and ptrLast 
                //(including ptrFirst but excluding ptrLast)
                else
                {
                    ptrFirst = ptrFirst->last;
                    --itemNum;
                    
                    Item *deletePtr = ptrFirst->next;
                    while(deletePtr->next!=ptrLast)
                    {
                        deletePtr = deletePtr->next;
                        delete deletePtr->last;
                    }
                    delete deletePtr;
                }

                // set the ptrFirst and ptrLast forward to find other repetition
                ptrFirst->next = ptrLast;
                ptrLast->last = ptrFirst;
                //in case of the ptrlast == nullptr and falling into forever loop.
                if (ptrLast != tail)
                {
                    ptrFirst = ptrLast;
                    ptrLast = ptrLast->next;
                }
            }// else: that is ptrLast != tail
        }//while(ptrLast != tail)
    }//if(ptrFirst != tail && ptrLast != tail )

    maxExp = tail->last->exp;
}

/* printing the polynomial in a power-descending order and in a mathematic format.
 e.g  x^2+2^x+1
 ##################################################################################*/
ostream& operator<<(ostream & out, const Polynomial &pl)
{
    //traverse the link from tail to head to make it in a power-descending order. 
    Item *ptr = pl.tail;
    //case1 : the polynomial is vacant
    if( ptr-> last == pl.head)
        out << "0";
    //case2: the polynomial has some items
    else
    {
        //first outputing the first item.
        //(pay attention to erasing the '+' if its coef is positive.)
        ptr = ptr->last;
        out << printItem(true, ptr->coef, ptr->exp);
        ptr = ptr->last;
        while(ptr != pl.head)
        {
            out << printItem(false, ptr->coef, ptr->exp);
            ptr = ptr->last;
        }
    }
    return out;
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

Polynomial & Polynomial::operator=(const Polynomial &pl)
{
    if( this != &pl )
    {
        //first deleting all the nodes between the head and the tail.
        Item *tempPtr = head->next;
        while( tempPtr->next != nullptr )
        {
                tempPtr = tempPtr->next;
                delete tempPtr->last;
        }
        head->next = tail;
        tail->last = head;
        itemNum = 0;
        maxExp = 0;
        //later adding the items and build a new polynomial.
        Item *tempPtr1 = head, *tempPtr2, *ptr = pl.head->next;
        while( ptr !=pl.tail )
        {
            tempPtr2 = new Item;
            tempPtr2->exp = ptr->exp;
            tempPtr2->coef = ptr->coef;
            tempPtr2->next = tail;
            tail->last = tempPtr2;
            tempPtr2->last = tempPtr1;
            tempPtr1->next = tempPtr2;
            tempPtr1 = tempPtr2;
            ++itemNum;
            ptr = ptr->next;
        }
    }
    return *this;
}


/* the addition of the polynomial
    ###################################################################
*/
Polynomial Polynomial::operator+(const Polynomial& anotherPoly)
{
    Polynomial p3;
    p3 = *this;
    Item *tempPtr1 = p3.head->next, *tempPtr2 = anotherPoly.head -> next;
    // while loop to traverse the nodes in two polynomials sequentially.
    while( tempPtr1 != p3.tail && tempPtr2 != anotherPoly.tail)
    {
        // if temPtr1->exp is smaller, we can ++ tempPtr1  
        //to find a proper place to insert the node of tempPtr2.  
        while( tempPtr1->exp < tempPtr2->exp 
            && tempPtr1->next != p3.tail )
        {
            tempPtr1 = tempPtr1->next;
        }
        //So now, whether tempPtr1->exp >= tempPtr2->exp 
        //or (tempPtr1->exp < tempPtr2->exp AND tempPtr1 == tail->last)

        // exp equals, add the coresponding coef and ++tempPtr2
        if( tempPtr1->exp == tempPtr2->exp )
        {
            tempPtr1->coef += tempPtr2->coef;
            
            // if that item is 0 after adding the corresponding one in tempPtr2. 
            if(tempPtr1->coef == 0)
            {
                Item* tempPtrDel = tempPtr1;
                tempPtr1->last->next = tempPtr1->next;
                tempPtr1->next->last = tempPtr1->last;
                tempPtr1 = tempPtr1->last;
                delete tempPtrDel;
                --itemNum;
            }
            tempPtr2 = tempPtr2->next;
        }
        else //exp not equals. 
        {
            //case 1. tempPtr1->exp > tempPtr2->exp
            // just insert the tempPtr2 between tempPtr1->last and tempPtr1 
           if( tempPtr1->exp > tempPtr2->exp ) 
            {
                Item *newTempPtr  = new Item;
                newTempPtr->coef = tempPtr2->coef;
                newTempPtr->exp = tempPtr2->exp;

                tempPtr1->last->next = newTempPtr;
                newTempPtr->last = tempPtr1->last;
                newTempPtr->next = tempPtr1;
                tempPtr1->last = newTempPtr;
                tempPtr2 = tempPtr2->next;
                ++itemNum;
                //Attention: here I have changed the property of the tempPtr2
                //(from the anotherpoly) , so non-const value pass is required.
            }
            // case 2. tempPtr1->exp < tempPtr2->exp AND tempPtr1 == tail->last
            // now the traverse for *this is over, we can break the while loop 
            //and insert the remaining nodes from anotherPoly to the back of *this. 
            else
                break;
        }
    }
    //insert the remaining nodes from anotherPoly to the back of *this
    while( tempPtr2 != anotherPoly.tail )
    {
        Item *newTempPtr  = new Item;
        newTempPtr->coef = tempPtr2->coef;
        newTempPtr->exp = tempPtr2->exp;

        p3.tail->last->next = newTempPtr;
        newTempPtr->last = p3.tail->last;
        newTempPtr->next = p3.tail;
        p3.tail->last = newTempPtr;
        tempPtr2 = tempPtr2->next;
        ++itemNum;
    }
    p3.maxExp = p3.tail->last->exp;
    return p3;
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

/* Similarly, the subtraction of the polynomial
    #####################################################################
*/
Polynomial Polynomial::operator-(const Polynomial &anotherPoly)
{
    Polynomial p3;
    p3 = *this;
    Item *tempPtr1 = p3.head->next, *tempPtr2 = anotherPoly.head -> next;
    // while loop to traverse the nodes in two polynomials sequentially.
    while( tempPtr1 != p3.tail && tempPtr2 != anotherPoly.tail)
    {
        // if temPtr1->exp is smaller, we can ++ tempPtr1  
        //to find a proper place to insert the node of tempPtr2.  
        while( tempPtr1->exp < tempPtr2->exp 
            && tempPtr1->next != p3.tail )
        {
            tempPtr1 = tempPtr1->next;
        }
        //So now, whether tempPtr1->exp >= tempPtr2->exp 
        //or (tempPtr1->exp < tempPtr2->exp AND tempPtr1 == tail->last)

        // exp equals, subtract the coresponding coef and ++tempPtr2
        if( tempPtr1->exp == tempPtr2->exp )
        {
            tempPtr1->coef -= tempPtr2->coef;
            
            // if that item is 0 after subtracting the corresponding one in tempPtr2. 
            if(tempPtr1->coef == 0)
            {
                Item* tempPtrDel = tempPtr1;
                tempPtr1->last->next = tempPtr1->next;
                tempPtr1->next->last = tempPtr1->last;
                tempPtr1 = tempPtr1->last;
                delete tempPtrDel;
                --itemNum;
            }
            tempPtr2 = tempPtr2->next;
        }
        else //exp not equals. 
        {
            //case 1. tempPtr1->exp > tempPtr2->exp
            // just insert the tempPtr2 between tempPtr1->last and tempPtr1 
           if( tempPtr1->exp > tempPtr2->exp ) 
            {
                Item *newTempPtr  = new Item;
                newTempPtr->coef = - tempPtr2->coef;
                newTempPtr->exp = tempPtr2->exp;

                tempPtr1->last->next = newTempPtr;
                newTempPtr->last = tempPtr1->last;
                newTempPtr->next = tempPtr1;
                tempPtr1->last = newTempPtr;
                tempPtr2 = tempPtr2->next;
                ++itemNum;
                //Attention: here I have changed the property of the tempPtr2
                //(from the anotherpoly) , so non-const value pass is required.
            }
            // case 2. tempPtr1->exp < tempPtr2->exp AND tempPtr1 == tail->last
            // now the traverse for *this is over, we can break the while loop 
            //and insert the remaining nodes from anotherPoly to the back of *this. 
            else
                break;
        }
    }
    //insert the remaining nodes from anotherPoly to the back of *this
    while( tempPtr2 != anotherPoly.tail )
    {
        Item *newTempPtr  = new Item;
        newTempPtr->coef = -tempPtr2->coef;
        newTempPtr->exp = tempPtr2->exp;

        p3.tail->last->next = newTempPtr;
        newTempPtr->last = p3.tail->last;
        newTempPtr->next = p3.tail;
        p3.tail->last = newTempPtr;
        tempPtr2 = tempPtr2->next;
        ++itemNum;
    }
    p3.maxExp = p3.tail->last->exp;
    return p3;
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

/*
    the multiply of two polynomials
    ############################################################
*/
Polynomial Polynomial::operator*(const Polynomial &anotherPoly)
{
    // initialize a temporary sum as 0
    Polynomial tempSum;
    Item *tempPtr1 = head->next, *tempPtr2 = anotherPoly.head->next;
    // e.g (1 + x)(2+ x^2)
    //first choose an item in the poly2.
    for (; tempPtr2 != anotherPoly.tail;tempPtr2 = tempPtr2 ->next)
    {
         Polynomial tempResult;
         Item *createPtr1 = tempResult.head;
         // use that chose item to multiply the poly1, 
         //store the temporary result into the tempResult.
         for (tempPtr1 = head->next; tempPtr1 != tail; tempPtr1 = tempPtr1->next)
         {
             Item *createPtr2 = new Item;
             createPtr2->coef = tempPtr2->coef * tempPtr1->coef;
             createPtr2->exp = tempPtr2->exp + tempPtr1->exp;
             createPtr2->next = tempResult.tail;
             tempResult.tail->last = createPtr2;
             createPtr2->last = createPtr1;
             createPtr1->next = createPtr2;
             createPtr1 = createPtr2;
             tempResult.itemNum++;
        }
        //adding up the tempResult to the tempSum.
        tempSum = tempSum + tempResult;
    }
    return tempSum;
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

/* 
an auxiliary function to polish each item in a mathematical format. 
*/
 string printItem(bool isFirst,double coef,int exp)
 {
    string ordi_OutputX = "x^", p1_OutPutX = "x", p0_outputX = "";
    string outputX, outputItem;
    // Firstly, checking the exponent( pay attention to 0 and 1)
    if(exp == 1)
        outputX = p1_OutPutX;
    else if(exp == 0)
        outputX = p0_outputX;
    //the normal situation where '^' is required.
    else
    {
        stringstream tempNum;
        tempNum << exp;
        outputX += ( ordi_OutputX + tempNum.str() ) ;
    }
    // then, checking the coef (positive to add '+', erase +-1 )
    if(coef < 0)
    {
        // erase the coef ,such as -x
        if( coef == -1 && exp != 0)
            outputItem = "-" + outputX;
       // keep the coef, such as -2x or -2 
       else
        {
            stringstream tempNum;
            tempNum << coef;
            outputItem = tempNum.str() + outputX;
        }
    }
    // the coef is positive
    else
    {
        // erase the coef ,such as +x
        if( coef == 1 && exp != 0)
            outputItem = "+" + outputX;
        // keep the coef, such as +2x or +2 
        else
        {
            stringstream tempNum;
            tempNum << coef;
            outputItem = "+" + tempNum.str() + outputX;
        }
    }        
    // erase the '+' of the first item if its coef is positive. 
     if( isFirst == true && coef > 0 )
     {
         outputItem.erase(0, 1);
     }
     return outputItem;
 }
/*
istream &operator>>(istream &in, const Polynomial &pl)
{
    string inputPoly;
    in >> inputPoly;
    int startPos = 0, currentPos = 0;
    auto itr = inputPoly.begin();
    for (; itr != inputPoly.end();++itr,++currentPos)
    {
        if( itr == ( --inputPoly.end() ) )
        {
             string inputItem = inputPoly.substr(startPos, currentPos);
            //extracting
        }
        if( *itr  == '+' || *itr == '-' )
        {
            string inputItem = inputPoly.substr(startPos, currentPos-1);
            //extracting
            startPos = currentPos;
        }
    }
}
*/
