#include <iostream>
using namespace std;
#include <string>
#include <vector>
void makeNext(const string& B, vector<int>& next)
{
	next[0] = -1;
	for(int i = 1, k = -1; i < B.length(); ++i)
	{
		while(k > -1 && B[i] != B[k+1]) k = next[k];
		
		if(B[k+1] == B[i]) next[i] = ++k;
		else next[i] = k;
	}
}
int KMP(const string& A, const string& B) {
        if(B.empty()) return 0;
        int A_len = A.length(), B_len = B.length();
 
        if(A_len < B_len) return -1;
	
        vector<int> next(B_len, -1);
        makeNext(B, next);
        cout << "DEBUG: the next array is "  << endl;
        for (auto itr = next.begin(); itr != next.end();++itr)
        {
            cout << *itr << endl;
        }

        
        for(int A_Start = 0, Cur_Idx = -1; A_Start+Cur_Idx+1 < A_len;)
        {
            if(A[A_Start + Cur_Idx + 1] == B[Cur_Idx+1])
            {
                ++Cur_Idx;
                if(Cur_Idx == B_len - 1) return A_Start;
            }
            else if(-1 != Cur_Idx)
            {
                A_Start += (Cur_Idx - next[Cur_Idx]);
                Cur_Idx = next[Cur_Idx];
            }
            else
            {
                A_Start++;
            }
                
        }
 
        return -1;
    }


int main()
{
    string mainString, subString;
    cout << "please input the mainstring.\n";
    cin >> mainString;
    cout << "please input the substring.\n";
    cin >> subString;
    int pos = KMP(mainString,subString);
    if(pos == -1)
        cout << "not a substring.\n";
    else
        cout << "is the substring starting from " << pos << endl;
    return 0;
}