
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    vector<string> str{"one", "two", "three", "four"};
    auto riter = find(str.begin(), str.end(), "one");
    str.insert(riter.base(), "five");
    vector<string>::iterator i1;
    for (i1 = str.begin(); i1 != str.end();i1++)
    {
        cout << *i1 << " ";
    }
    cout << str[2] << endl;

    /*
    vector<string> words{"one","three"};
    auto iter = words.emplace(++begin(words), "two");
    //words.emplace(++iter, "three");
    vector<string> more{"four","five"};
    iter = words.insert(--words.end(), more.begin(), more.end());
    words.insert(--words.end(), "ten");
    vector<string>::iterator i1;
    for (i1 = words.begin(); i1 != words.end();i1++)
    {
        cout << *i1 << " ";
    }

    vector<int> v;  //v是存放int类型变量的可变长数组，开始时没有元素
    
    for (int n = 0; n<5; ++n)
        v.push_back(n);  //push_back成员函数在vector容器尾部添加一个元素
    
    vector<int>::iterator i;  //定义正向迭代器
    for (i = v.begin(); i != v.end(); ++i) {  //用迭代器遍历容器
        cout << *i << " ";  //*i 就是迭代器i指向的元素
        *i *= 2;  //每个元素变为原来的2倍
    }
    cout << endl;
    //用反向迭代器遍历容器
    for (vector<int>::reverse_iterator j = v.rbegin(); j != v.rend(); ++j)
        cout << *j << " ";
    */
}