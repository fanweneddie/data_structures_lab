#ifndef CIRCULARLINK
#define CIRCULARLINK

// can I inherit a universe circular link to make a Joseph ring???
// ADT for single-direction circular ring with a head node 
template<class T>
struct Node
{
    T data1;
    T data2;
    Node *next;
};

template<class T>
class CircularLink
{
    private:
        Node<T>* head;
        int size;
    public:
        CircularLink();
        Node<T> *get_head() const { return head; }
        int get_size() const { return size; }
        void push_back( const T& insertData1,const T& insertData2 );
        void insert(int order, const T& insertData1, const T& insertData2 );
        void erase(int index);
        void erase(Node<T> *deletePtr);
        ~CircularLink();
};

template<class T>
CircularLink<T>::CircularLink()
{
    head = new Node<T>;
    head->next = head;
    size = 0;
}

/*
insert function
input: the index of place to insert, the number and the code of that player
output: a circularlink with one more node.
*/
template <class T>
void CircularLink<T>::insert(int index, const T &insertData1, const T &insertData2)
{
    //if the index is too big or too little, it will throw an exception.
    if( index > size )
    { 
        throw "the index is larger than the size of the circularLink.\n";
    }
    if (index < 0)
    { 
        throw "the index number is lower than 0.\n";
    }
    Node<T> *ptr = head;
    //go to the expected place.
    for (int i = 0; i < index; ++i)
    {
        ptr = ptr->next;
    }
    //insert a node.
    Node<T>* newNode = new Node<T>;
    newNode->next = ptr->next;
    ptr->next = newNode;
    newNode->data1 = insertData1;
    newNode->data2 = insertData2;
    ++size;
}

template <class T>
void CircularLink<T>::push_back(const T& insertData1, const T& insertData2)
{
    if(size > 0 )
        insert(size , insertData1,insertData2);
    else
        insert(0, insertData1, insertData2);
}

template<class T>
void CircularLink<T>::erase(int index)
{
   if( index > size )
    { 
        throw  "the index is larger than the size of the circularLink.\n";
    }
        if (index < 0)
    { 
         throw "the index number is lower than 0.\n";
    }

    Node<T>* ptr = head;
    for (int i = 0; i < index;++i)
    {
        ptr = ptr->next;
    }
    Node<T> *tempPtr = ptr -> next;
    ptr->next = ptr->next->next;
    delete tempPtr;
    --size;
}

/*
erase the node that we anticipated.
input: a node that we want to erase.
output: a revised circularLink.
*/
template <class T>
void CircularLink<T>::erase( Node<T>* deletePtr)
{
    //try to traverse the link to find the anticipated node.
    Node<T>* ptr = head;
    while( ptr->next != head && ptr->next != deletePtr)
    {
        ptr = ptr->next;
    }
    //can not find the node.
    if( ptr -> next == head )
    {
        throw "fail to find the deletePtr to erase the node.\n";
    }
    //delete the node that we have found
    Node<T> *tempPtr = ptr -> next;
    ptr->next = ptr->next->next;
    delete tempPtr;
    --size;
}

template<class T>
CircularLink<T>::~CircularLink()
{
    Node<T> *frontPtr = head, *rearPtr = head->next;
    for (int i = 0; i < size ;++i)
    {
        frontPtr = rearPtr;
        rearPtr = rearPtr->next;
        delete frontPtr;
    }
    delete rearPtr;
}

#endif