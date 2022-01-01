#include "realNumber.h"
// constructor
RealNumber::RealNumber()
{
    //using . to first initialize the decimal number.
    //initialize other members as 0;
    decNum.push_front('.');
    integerLen = 0;
    decimalLen = 0;
    isPositive = true;
    isInteger = true;
    NSystemNum = decNum;
    N = 0;
}

//copy constructor
RealNumber::RealNumber(const RealNumber &otherNum)
{
    decNum = otherNum.decNum;
    integerLen = otherNum.integerLen;
    decimalLen = otherNum.decimalLen;
    isPositive = otherNum.isPositive;
    isInteger = otherNum.isInteger;
    NSystemNum = otherNum.NSystemNum;
    N = otherNum.N;
}

void RealNumber::renew_intLen()
{
    int intlen = 0;
    list<char>::iterator itr = decNum.begin();
    while( *itr != '.' )
    {
        ++intlen;
        ++itr;
    }
    integerLen = intlen;
}

void RealNumber::renew_decLen()
{
    int declen = 0;
    list<char>::reverse_iterator ritr = decNum.rbegin();
    while( *ritr != '.' )
    {
        ++declen;
        ++ritr;
    }
    integerLen = declen;
}

// overload for the assignment operator
RealNumber & RealNumber::operator=(const RealNumber &otherNum)
{
    if( this != &otherNum )
    {
        decNum = otherNum.decNum;
        integerLen = otherNum.integerLen;
        
        decimalLen = otherNum.decimalLen;
        isPositive = otherNum.isPositive;
        isInteger = otherNum.isInteger;
        NSystemNum = otherNum.NSystemNum;
        N = otherNum.N;
    }
    return *this;
}
