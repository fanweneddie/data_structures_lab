#ifndef SEQSTACK
#define SEQSTACK

const int STACK_INITIAL_SIZE = 20;
const int STACK_INCREMENT = 10;

//
template<class T>
class SeqStack
{
    private:
        T* base;
        T* top;
        int size;
        int capacity;

    public:
        SeqStack();
        SeqStack(T* seqList,int listSize);
        SeqStack(const SeqStack &otherSeqstack);

        void clear();
        bool is_empty() const { return top == base; }
        int get_size() const { return size; }
        int get_capacity() const { return capacity; }
        T &get_top();

        void push(const T &element);
        T &pop();

        ~SeqStack()
        {
            delete base;
        }
};

#endif