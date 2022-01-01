#include "constructors.cpp"
//input the real number.
//(if the input is invalid such as "12.", it will throw an exception)
istream& operator>>(istream &in, RealNumber &Num)
{
    string inputNum;
    in >> inputNum;

    string::iterator stringItr = inputNum.begin();
    list<char>::iterator insertItr = Num.decNum.begin();
    //deal with the negative sign in the inputNum
    if( *stringItr == '-')
    {
        Num.isPositive = false;
        ++stringItr;
    }
    else
        Num.isPositive = true;
    //duplicate the integral part of the inputNum to Num.decNum
    while( stringItr != inputNum.end() && *stringItr != '.'  )
    {
        Num.decNum.insert(insertItr, *stringItr);
        ++stringItr;
        ++Num.integerLen;
    }
    //there is no '.' in the inputNum, showing that it is an integer.
    if( stringItr == inputNum.end() )
    {
        Num.isInteger = true;
    }
    //there is a '.', showing that it may be a valid decimal num.
    else
    {
        Num.isInteger = false;
        ++stringItr;
        // the inputNum is "xxx." , invalid decimal part.
        if( stringItr == inputNum.end() )
            throw "invalid input: having a decimal point but doesn't have decimal part.\n";
        //valid decimal part, we will replicate it into the decNum.
        else
        {
            while (stringItr != inputNum.end())
            {
                Num.decNum.push_back(*stringItr);
                ++stringItr;
                ++Num.decimalLen;
            }
        }
    }
    return in;
}
//output the decimal part of the real number.
ostream & operator << (ostream &out , const RealNumber & Num)
{
    //don't forget to output the negative sign!
    if( !Num.isPositive )
        out << "-";
    auto listItr = Num.decNum.begin();
    // if the num is not an integer, we need to print its decimal point and its decimal part
    if( !Num.isInteger )
    {
        for (; listItr != Num.decNum.end();++listItr)
            out << *listItr;
        return out;
    }
    // if the num is an integer, we don't need to print the decimal point
    else
    {
        for (; *listItr != '.';++listItr)
            out << *listItr;
        return out;   
    }
}
