//big integral number adding

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LongInt
{
    protected:
        vector<char> digits;
        int len;
        string intName;

    public:
        LongInt();
        vector<char> get_digits() const;
        int get_len();
        string get_name() const;
        friend istream &operator>>(istream &instream, LongInt &bigNumber);
        friend ostream &operator<<(ostream &outstream, const LongInt &bigNumber);
        //getting the i st least digit(starting from 0), which can help add.
        char get_least_digit(int i);
        
        LongInt operator+( LongInt &BigNumber);
        ~LongInt()
        {}
};

//default constructor, set the number as 0
LongInt::LongInt()
{
    digits = {'0'};
    len = 1;
}

//getting the value of the three protected values
vector<char> LongInt::get_digits() const
{
    vector<char> temp(digits);
    return temp;
}

int LongInt::get_len() 
{
    len = digits.size();
    return len;
}

string LongInt::get_name() const
{
    return intName;
}

//override >> to input the big number.
istream& operator >>(istream &instream, LongInt &bigNumber)
{
    const char LOWEST_DIGIT = '0';
    const char HIGHEST_DIGIT = '9';
    const char SENTINEL = 'X';
    char digit_char;

    bigNumber.digits.erase(bigNumber.digits.begin(), bigNumber.digits.end());
    
    do
    {
        instream >> digit_char;
        if( digit_char <= HIGHEST_DIGIT && digit_char >= LOWEST_DIGIT )
        {
            bigNumber.digits.push_back(digit_char - LOWEST_DIGIT);
        }
        else
            cout << "INPUT DONE\n";
    } while (digit_char != SENTINEL);
    bigNumber.len = bigNumber.digits.size();
    return instream;
}

// override << to output a big number
ostream& operator <<(ostream &outstream,LongInt &bigNumber)
{
    vector<char> digitsTemp( bigNumber.get_digits() );
    for (auto iter1 = digitsTemp.begin(); iter1 != digitsTemp.end(); ++iter1)
    {
        outstream << (int)*iter1;
    }
    return outstream;
}

char LongInt::get_least_digit(int i) 
{
    int len = this->get_len();
    if( i>=len )
        return '0';
    else
        return digits[len - i - 1];
}

//override + to make addition
LongInt LongInt::operator + ( LongInt &bigNumber)
{
    int carry = 0, largerLen, partialSum;
    vector<char> digits2 = bigNumber.get_digits();
    int len2 = bigNumber.get_len();
    len = this->digits.size();
    LongInt sum;
    sum.digits.erase(sum.digits.begin(), sum.digits.end());
    largerLen = len > len2 ? len : len2;

    for (int i = 0; i < largerLen;i++)
    {
        partialSum = get_least_digit(i) + bigNumber.get_least_digit(i) + carry;
        carry = partialSum / 10;
        sum.digits.push_back(partialSum % 10);
    }

    if(carry ==1)
        sum.digits.push_back(carry);
    //reverse the sum.digits
    auto iterFront = sum.digits.begin();
    auto iterBack = (--sum.digits.end());
    while(iterFront < iterBack)
    {
        char tempChar = *iterFront;
        *iterFront = *iterBack;
        *iterBack = tempChar;
        iterFront++;
        iterBack--;
    }
    return sum;
}

int main()
{
    LongInt bigNumber1, bigNumber2,sum;
    cout << "please input the value of bigNumber1.(the sentinel is X)\n";
    cin >> bigNumber1;
    cout << "bigNumber1 is " << bigNumber1 << endl;
    cout << "please input the value of bigNumber2.(the sentinel is X)\n";
    cin >> bigNumber2;
    cout << "bigNumber2 is " << bigNumber2 << endl;
    sum = bigNumber1 + bigNumber2;
    cout << "the sum is " << sum << endl;
    return 0;
}