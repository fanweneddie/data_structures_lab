#ifndef CIRCULARQUEUE
#define CIRCULARQUEUE
const int MAXSIZE = 20;

template<class T>
class CircularQueue
{
    private:
        T *base;
        int front;
        int rear;
        int size;
    public:
        CircularQueue();
        CircularQueue(const CircularQueue &otherQueue);
        int get_size() const { return size; }
        bool is_empty() const { return size == 0; }
        void enQueue(const T &ele);
        T& get_frontElement() const;
        void deQueue();
        ~CircularQueue();
};

template<class T>
CircularQueue<T>::CircularQueue()
{
    base = new T[MAXSIZE];
    front = 0;
    rear = 0;
    size = 0;
}

template<class T>
 CircularQueue<T>::CircularQueue(const CircularQueue &otherQueue)
 {
     base = new T[MAXSIZE];
     front = 0;
     int tempIndex1 = front;
     int tempIndex2 = otherQueue.front;
     while( tempIndex2 != otherQueue.rear)
     {
         *(base + tempIndex1) = *(otherQueue.base + tempIndex2);
         tempIndex1 = (tempIndex1 + 1) % MAXSIZE;
         tempIndex2 = (tempIndex2 + 1) % MAXSIZE;
     }
     rear = tempIndex1;
     size = otherQueue.size;
 }

template<class T>
void CircularQueue<T>::enQueue(const T &ele)
{
    if( ( rear + 1) % MAXSIZE == front )
        throw "the queue is full, fail to enqueue.\n";
    else
    {
        *(base + rear) = ele;
        rear = (rear + 1) % MAXSIZE;
        ++size;
    }
}

template<class T>
T& CircularQueue<T>::get_frontElement() const
{
    if( rear == front )
        throw "the queue is empty, fail to get element.\n";
    else
        return *( base + front );
}

template<class T>
void CircularQueue<T>::deQueue()
{
    if( rear == front )
        throw "the queue is empty, fail to dequeue.\n";
    else
    {
        front = (front + 1) % MAXSIZE;
        --size;
    }
}

template<class T>
CircularQueue<T>::~CircularQueue()
{
    delete[] base;
}

#endif

