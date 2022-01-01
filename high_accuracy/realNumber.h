#ifndef REALNUMBER
#define REALNUMBER
#include <list>
#include <iostream>
#include <string>
#include <stack>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::list;
using std::ostream;
using std::stack;
using std::string;
using std::vector;

class RealNumber
{
    public:
        list<char> decNum;
        bool isPositive;
        bool isInteger;
        int integerLen;
        int decimalLen;
        list<char> NSystemNum;
        int N;

    public:
        RealNumber();
        RealNumber(const RealNumber &otherNum);
        //inputting the real number.
        friend istream &operator>>(istream &in,  RealNumber &Num);
        //system conversion from decimal system to N system.
        int get_intLen() const { return integerLen; }
        int get_decLen() const { return decimalLen; }
        void renew_intLen();
        void renew_decLen();
        void systemConversion(int inputN);
        // arismatic calculation for + - and *
        RealNumber absAddition(RealNumber otherNum);
        RealNumber absSubtraction( RealNumber otherNum);
        RealNumber operator+( RealNumber otherNum);
        RealNumber operator-( RealNumber otherNum);
        RealNumber operator*( RealNumber otherNum);
        RealNumber &operator=(const RealNumber &otherNum);
        bool operator > (const RealNumber& otherNum);
        bool operator==(const RealNumber &otherNum);
        friend ostream & operator << (ostream &out , const RealNumber & Num);
        ~RealNumber()
        {}
};

// abs addition with high accuracy (making preparation for the addition)
RealNumber RealNumber::absAddition(RealNumber otherNum)
{
    cout << "debug0.22 : before the renew\n";
    cout << "debug 0.22 the integer len of this is " << integerLen << endl;
    cout << "debug 0.22 the integer len of othernum is " << otherNum.integerLen << endl;
    renew_intLen();
    renew_decLen();
    otherNum.renew_intLen();
    otherNum.renew_decLen();
    //adding 0 to the high place of the integer which has a smaller integer length.
    if( integerLen < otherNum.integerLen)
    {
        for (int i = 0; i < otherNum.integerLen - integerLen;++i)
        {
            cout << "adding front 0  to this \n";
            decNum.push_front('0');       
        }
    }   
    else
     {
        for (int i = 0; i < integerLen - otherNum.integerLen ;++i)
            otherNum.decNum.push_front('0');       
    }

    cout << "debug1.6: this decimal len is " << decimalLen << endl;
    cout << "debug1.6: otherNum decimal len is " << otherNum.decimalLen << endl;
    //adding 0 to the low place of decimal which has a smaller decimal length.
    if( decimalLen < otherNum.decimalLen)
    {
        cout << "this is being added with 0\n";
        for (int i = 0; i < otherNum.decimalLen - decimalLen;++i)
            decNum.push_back('0');
        cout << "now this is " << *this << endl;
    }   
    else
     {
        for (int i = 0; i < decimalLen -  otherNum.decimalLen  ;++i)
            otherNum.decNum.push_back('0');       
    }
    cout << "after adding 0 \n";
    cout << "debug1.6: this decimal len is " << decimalLen << endl;
    cout << "debug1.6: otherNum decimal len is " << otherNum.decimalLen << endl;
    RealNumber resultNum(*this);
    int tempCarry = 0,tempResult = 0;
    cout << "debug2: this is " << *this << endl;
    cout << "debug2: the otherNum is " << otherNum << endl;
    list<char>::reverse_iterator ritr1 = decNum.rbegin();
    list<char>::reverse_iterator ritr2 = otherNum.decNum.rbegin();
    list<char>::reverse_iterator ritr3 = resultNum.decNum.rbegin();
    while( ritr1 != decNum.rend() )
    {
        //escape the decimal point.
        if(*ritr1 == '.')
        {
            ++ritr1;
            ++ritr2;
            ++ritr3;
        }
        else
        {
            cout << "ritr1 is " << *ritr1 << endl;
            cout << "ritr2 is " << *ritr2 << endl;
            tempResult =  tempCarry + *ritr1 + *ritr2 - '0' - '0';
            tempCarry = tempResult / 10;
            *ritr3 = tempResult % 10 + '0';
            ++ritr1;
            ++ritr2;
            ++ritr3;
        }
    }
    if(tempCarry)
        resultNum.decNum.push_front('1');
    
    ritr3 = resultNum.decNum.rbegin();
    if( *ritr3 != '.' )
        resultNum.isInteger = false;
    else
        resultNum.isInteger = true;
    cout << "debug101: before the renew, the int len of result num is " << resultNum.integerLen << endl;
    resultNum.renew_intLen();
    cout << "debug100: IN THE ADDITION, the new int len of result num is " << resultNum.integerLen << endl;
    resultNum.renew_decLen();
    return resultNum;
}

//abs subtraction with high accuracy (making preparation for subtraction)
RealNumber RealNumber::absSubtraction(RealNumber otherNum)
{
     renew_intLen();
    renew_decLen();
    otherNum.renew_intLen();
    otherNum.renew_decLen();
    cout << "debug1.5: this " << *this << endl;
    cout << "debug1.5: otherNum " << otherNum << endl;
    //adding 0 to the high place of the integer which has a smaller integer length.
    if( integerLen < otherNum.integerLen)
    {
        for (int i = 0; i < otherNum.integerLen - integerLen;++i)
            decNum.push_front('0');       
    }   
    else
     {
        for (int i = 0; i < integerLen - otherNum.integerLen ;++i)
            otherNum.decNum.push_front('0');       
    }

    //adding 0 to the low place of decimal which has a smaller decimal length.
    if( decimalLen < otherNum.decimalLen)
    {
        for (int i = 0; i < otherNum.decimalLen - integerLen;++i)
            decNum.push_back('0');       
    }   
    else
     {
        for (int i = 0; i < decimalLen -  otherNum.decimalLen  ;++i)
            otherNum.decNum.push_back('0');       
    }

    RealNumber resultNum(*this);
    int tempCarry = 0,tempResult = 0;
    //let the bigger number subtract the smaller number.
    list<char>::reverse_iterator ritr1, ritr2;
    list<char>::reverse_iterator ritr3 = resultNum.decNum.rbegin();
    cout << "debug2: this " << *this << endl;
    cout << "debug2: otherNum " << otherNum << endl;
    isPositive = true;
    otherNum.isPositive = true;
    if(*this > otherNum)
    {
        ritr1 = decNum.rbegin();
        ritr2 = otherNum.decNum.rbegin();
        resultNum.isPositive = true;
        cout << "debug3: this is bigger than otherNum\n";
        cout << "debug3: this " << *this << endl;
        cout << "debug3: otherNum " << otherNum << endl;
    }
    else
    {
        cout << "debug3.1: this is smaller than otherNum\n";
        cout << "debug3: this " << *this << endl;
        cout << "debug3: otherNum " << otherNum << endl;
        ritr2 = decNum.rbegin();
        ritr1 = otherNum.decNum.rbegin();
        resultNum.isPositive = false;
    }
    while( ritr1 != decNum.rend() && ritr1 != otherNum.decNum.rend() )
    {
        //escape the decimal point.
        if(*ritr1 == '.')
        {
            ++ritr1;
            ++ritr2;
            ++ritr3;
        }
        else
        {
            cout << "ritr1 is " << *ritr1 << endl;
            cout << "ritr2 is " << *ritr2 << endl;
            tempResult =  tempCarry + *ritr1 - *ritr2 ;
            tempCarry = tempResult < 0 ? -1 : 0;
            tempResult = tempResult < 0 ? tempResult + 10 : tempResult;
            *ritr3 = tempResult + '0';
            ++ritr1;
            ++ritr2;
            ++ritr3;
        }
    }

    ritr3 = resultNum.decNum.rbegin();
    if( *ritr3 != '.' )
        resultNum.isInteger = false;
    else
        resultNum.isInteger = true;

    resultNum.renew_intLen();
    resultNum.renew_decLen();
    return resultNum;
}

//overload operator + (with high accuracy and can deal with the negative numbers)
RealNumber RealNumber::operator+( RealNumber otherNum)
{
     renew_intLen();
    renew_decLen();
    otherNum.renew_intLen();
    otherNum.renew_decLen();
    if( isPositive && otherNum.isPositive )
    {
        cout << "debug1 : enter the first mode : pos + pos\n";
        cout << "debug1.1 : the int len of this is " << integerLen << endl;
        cout << "debug1.2 : the int len of otherNum is " << otherNum.integerLen << endl;
        RealNumber tempRN = absAddition(otherNum) ;
        cout << "debug99:OUT OF ADDITION ,BEFORE RENEW, the int len of the result is "  << tempRN.integerLen << endl;
        tempRN.renew_intLen();
        tempRN.renew_decLen();
        cout << "debug99:OUT OF ADDITION,AFTER RENEW, the int len of the result is "  << tempRN.integerLen << endl;
        cout << "the value of rN is " << tempRN<< endl;
        return tempRN;
    }
    else if (isPositive && !otherNum.isPositive)
    {
            cout << "debug1: enter the second mode. pos + neg\n";
            RealNumber tempRN( absSubtraction(otherNum) );
            cout << "debug99:OUT OF ADDITION ,BEFORE RENEW, the int len of the result is "  << tempRN.integerLen << endl;
            tempRN.renew_intLen();
            tempRN.renew_decLen();
            cout << "debug99:OUT OF ADDITION,AFTER RENEW, the int len of the result is "  << tempRN.integerLen << endl;
            cout << "the value of rN is " << tempRN<< endl;
            return tempRN;
    }
    else if (!isPositive && otherNum.isPositive)
     {
         cout << "debug1: enter the third mode. neg + pos\n";
         RealNumber tempRN( otherNum.absSubtraction(*this) );
        cout << "debug99:OUT OF ADDITION ,BEFORE RENEW, the int len of the result is "  << tempRN.integerLen << endl;
        tempRN.renew_intLen();
        tempRN.renew_decLen();
        cout << "debug99:OUT OF ADDITION,AFTER RENEW, the int len of the result is "  << tempRN.integerLen << endl;
        cout << "the value of rN is " << tempRN<< endl;
        return tempRN;
     }
    else
    {
        cout << "debug1: enter the fourth mode. neg + neg\n";
        RealNumber resultNum = absAddition(otherNum);
        resultNum.isPositive = false;
        resultNum.renew_intLen();
        resultNum.renew_decLen();
        return resultNum;
    }
}

//overload operator - (with high accuracy and can deal with the negative numbers)
RealNumber RealNumber::operator-( RealNumber otherNum)
{
    //case 1 : positive - positive
    renew_intLen();
    renew_decLen();
    otherNum.renew_intLen();
    otherNum.renew_decLen();
    if( isPositive && otherNum.isPositive )
    {
        cout << "debug1 : enter the first mode : pos - pos\n";
        RealNumber resultNum = absSubtraction(otherNum);
        resultNum.renew_intLen();
        resultNum.renew_decLen();
        return resultNum;
    }
    //case 2 : positive - negative
    else if (isPositive && !otherNum.isPositive)
    {
        cout << "debug1: enter the second mode. pos - neg\n";
        RealNumber resultNum = absAddition(otherNum);
        resultNum.renew_intLen();
        resultNum.renew_decLen();
        return resultNum;
    }
    //case 3 : negative - positive 
    else if (!isPositive && otherNum.isPositive)
     {
        cout << "debug1: enter the third mode. neg - pos\n";
        RealNumber resultNum = absAddition(otherNum);
        resultNum.isPositive = false;
        resultNum.renew_intLen();
        resultNum.renew_decLen();
        return resultNum;
     }
     // case 4: negative - negative
    else
    {
        cout << "debug1: enter the fourth mode. neg - neg\n";
        RealNumber resultNum = otherNum.absSubtraction(*this);
        resultNum.renew_intLen();
        resultNum.renew_decLen();
        return resultNum;
    }
}


//overload operator for > (however, how about 12.00 and 12.0 ?)
bool RealNumber::operator > (const RealNumber& otherNum)
{
    //first,quick judgement for the numbers with different sign
    if( isPositive && !otherNum.isPositive)
        return true;
    if(! isPositive && otherNum.isPositive)
        return false;
    
    // then, with the same sign,compare the abs.
    // 1. this abs is bigger      2. equals       3. this abs is smaller 
    int  thisAbsBigger = 0;
    if( integerLen > otherNum.integerLen )
        thisAbsBigger = 1;
    else
    {
        if(integerLen < otherNum.integerLen )
            thisAbsBigger = -1;
        // integerLen is the same,so we have to compare the value of each digit.
        else 
        {
            list<char>::iterator itr1 = decNum.begin();
            list<char>::const_iterator itr2 = otherNum.decNum.begin();
            while(itr1 != decNum.end() && itr2 != otherNum.decNum.end() )
            {   
                if( *itr1 > *itr2 )
                {
                    thisAbsBigger = 1;
                    break;
                }
                if(*itr1 < *itr2 )
                {
                    thisAbsBigger = -1;
                    break;
                }
                ++itr1;
                ++itr2;
            }
            if( itr1 == decNum.end() && itr2 != otherNum.decNum.end() )
                thisAbsBigger = -1;
            if( itr1 != decNum.end() && itr2 == otherNum.decNum.end() )
                thisAbsBigger = 1;
            if( itr1 == decNum.end() && itr2 == otherNum.decNum.end() )
                thisAbsBigger = 0;
        }
    }

    // we have compared the abs, then just need to integrade its result with the sign.
    if(isPositive && otherNum.isPositive)
        return thisAbsBigger == 1 ? true : false;
    else
         return thisAbsBigger == -1 ? true : false;
}



RealNumber RealNumber::operator*( RealNumber otherNum)
{
    list<RealNumber> adders;
    RealNumber ResultNum;
    cout << "debug0: this is " << *this << endl;
    cout << "debug0: otherNum is " << otherNum << endl;
    list<char>::reverse_iterator ritr1 = decNum.rbegin();
    list<char>::reverse_iterator ritr2 = otherNum.decNum.rbegin();
    int digitWeight = 1;
    for (; ritr2 != otherNum.decNum.rend(); ++ritr2)
    {
        if( *ritr2 == '.')
        {
            cout << "debug0.1 : ritr2 has met the decimal point.\n";
            continue;
        }
        RealNumber tempResult;
        for (int i = 1; i < digitWeight;++i)
        {
            cout << "adding 0 for the tempResult.\n";
            tempResult.decNum.push_front('0');
            ++tempResult.integerLen;
        }
        
        int resulti = 0, carryi = 0;
        for (ritr1 = decNum.rbegin(); ritr1 != decNum.rend(); ++ritr1)
        {
            if( *ritr1 == '.')
                continue;
            cout << "ritr2 is " << *ritr2 << endl;
            cout << "ritr1 is " << *ritr1 << endl;
            resulti = (*ritr2 - '0') * (*ritr1 - '0') + carryi;
            carryi = resulti / 10;
            resulti = resulti % 10;
            tempResult.decNum.push_front(resulti + '0');
            ++tempResult.integerLen;
        }
        if(carryi != 0)
        {
            tempResult.decNum.push_front(carryi + '0');
            ++tempResult.integerLen;
        }
        cout << " the temp result is " << tempResult << endl;
        cout << "the integerlen of tempResult is " << tempResult.integerLen << endl;
        adders.push_back(tempResult);
        ++digitWeight;
    }

    list<RealNumber>::iterator adderItr1 =  adders.begin();
    list<RealNumber>::iterator adderItr2 = ++( adders.begin() );
    cout << "debug1.4 : the int length of the addItr1 is " << (*adderItr1).integerLen << endl;
    cout << "debug1.4 : the int length of the addItr2 is " << (*adderItr2).integerLen << endl;
    ResultNum = *adderItr1 + *adderItr2;
    ++adderItr2;
    while( adderItr2 != adders.end() )
    {
        ResultNum = ResultNum + *adderItr2;
        ++adderItr2;
    }

    if( ( isPositive && otherNum.isPositive ) || ( !isPositive && ! otherNum.isPositive) )
        ResultNum.isPositive = true;
    else
        ResultNum.isPositive = false;
    
    int total_decimalLen = decimalLen + otherNum.decimalLen;
    if(total_decimalLen != 0)
    {
        ResultNum.decNum.pop_back();
        auto insertItr = ResultNum.decNum.end();
        for (int i = 0; i < total_decimalLen;++i)
        {
            --insertItr;
        }
        ResultNum.decNum.insert(insertItr, '.');
    }

    return ResultNum;
    
}


#endif