#ifndef SINGLEQUEUE
#define SINGLEQUEUE
template<class T>
struct Node 
{
    T data;
    Node *next;
};

template<class T>
class SingleQueue
{
    private:
        Node<T> *front;
        Node<T>* rear;
        int len;
    public:
        SingleQueue();
        SingleQueue(const SingleQueue &otherQue);
        void clear();
        bool is_empty() const { return front == rear ? true : false; }
        int get_len() const { return len; }
        Node<T> *get_frontNode() const { return front; }
        T& get_frontEle() const;
        void enQueue(const T &ele);
        void deQueue();
        ~SingleQueue();
};
#endif