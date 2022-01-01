#include<iostream>
using namespace std;
string make_plural(size_t,const string&,const string&);
const string &shorterString(const string &,const string &);
const string mainip(const string&);
char &get_val(string &,string::size_type);

int main()  
{      
	cout<<make_plural(1,"dog","s")<<endl;      
	cout<<make_plural(2,"dog","s")<<endl;           
	string string1="1234";      
	string string2="abc";      
	cout<<shorterString(string1,string2)<<endl;            
	cout<<mainip("jiajia")<<endl;                  
	string s("123456");      
	cout<<s<<endl;      
	get_val(s,0)='a';            
	cout<<s<<endl;            
	getchar();      
	return 0;  
}  

//返回非引用   
string make_plural(size_t i,const string &word,const string &ending)  
{
      return (i==1)?word:word+ending;  
}  

//返回引用   
const string &shorterString(const string &s1,const string &s2)  
{      
      return s1.size()<s2.size()?s1:s2;  
}
//禁止返回局部对象的引用（我的dev c++ 没有报错，比较可怕）
const string mainip(const string &s)  
{      
	string ret=s;      
	return ret; 
} 
 //引用返回左值  
 char &get_val(string &str,string::size_type ix)
   {      
   		return str[ix];  
   }  
