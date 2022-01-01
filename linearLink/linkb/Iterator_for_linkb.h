#include <iterator>
#include <algorithm>
using namespace std;
//the iterator is intended for linkb,so it need to use next ptr to ++;
template<class T>
class MyIterator : public iterator<input_iterator_tag,T>
{
    protected:
        T *pt;

    public:
        //two constructors
        MyIterator(T *pt)
        {
            this->pt = pt;
        }
        MyIterator(const MyIterator &it)
        {
            this->pt = it.pt;
        }

        MyIterator &operator=(const MyIterator &it)
        {
            this->pt = it.pt;
            return *this;
        }

        bool operator==(const MyIterator &it)
        {
            return (this->pt == it.pt);
        }

        //++it;
        //however, since the address of the nodes of a linkb
        //is discrete, we had better use the next pointer.
        MyIterator& operator++()
        {
            this->pt++;
            return *this;
        }

        //it++;
        MyIterator &operator++(int)
        {
            MyIterator temp = *this;
            this->pt++;
            return temp;
        }

        //using * as a reference
        T &operator*()
        {
            return *(this->pt);
        }

        ~MyIterator()
        {}
};