#ifndef LINKB
#define LINKB

#include <iostream>
#include "Iterator.h"
using namespace std;

/*
the linkb is a link with double direction,just like list
it has some basic functions such as

Linkb(int maxSize = 0);
Node* create();

bool is_full() const
bool is_empty() const

Node* get_head() const
Node* get_tail() const
int get_size() const

void push_back(const T &inputItem)
void push_front(const T &inputItem)

/// actually that is different from the list
/// because list can not use index reference. 
T& operator[](int k)  

int find_first_of_item(const T& inputItem) const
int find_last_of_item(const T& inputItem) const

///iterator

void delet(int k)
void delet(T& inputItem)
~Linkb()

*/
template <class T>
class Linkb
{
    protected:
        struct Node
        {
            T item;
            Node* next;
            Node *last;
        };
    
        Node *head ;
        int size ;

    public:    
        
        //constructor, constructing a link without any input.
        Linkb(int maxSize = 0)
        {
            head = new Node;
            //we should keep the head as not nullptr even the size is 0
            if(maxSize == 0)
            {
                head->next = nullptr;
                head->last = nullptr;
                size = 0;
                return;
            }

            int sizeBuilt = 0;
            Node *temp = head;

            while(sizeBuilt < maxSize)
            {
                Node *s = new Node;
                s -> last = temp;
                temp -> next = s;
                temp = s;
                sizeBuilt++;
            }
            size = 0;
            head -> last = nullptr;
            temp->next = nullptr;
        }

        //create a new link by input. set -1 as the sentinel.
        Node* create()
        {
            Node *p = head;
            bool cycle = true;
            T inputItem;
            while( cycle )
            {
                cout << "please input the data for the link." << endl;
                cin >> inputItem;
                if( inputItem != -1 )
                {
                    Node *newNode = new Node;
                    newNode->item = inputItem;
                    p->next = newNode;
                    newNode->last = p;
                    p = newNode;
                    size++;
                }
                else
                {
                    cycle = false;
                    cout << "input done." << endl;
                }
            }
            p->next = nullptr;
            head = head->next;
            head->last = nullptr;
            return head;
        }

        //checking whether the link is full
        bool is_full() const
        {
            Node* temp = head;
            int sizeDetected = 0;
            while(temp != nullptr)
            {
                temp = temp->next;
                sizeDetected++;
            }
            if(sizeDetected == size)
                return true;
            else
                return false;
        }

        //checking whether the link is empty
        bool is_empty() const
        {
            if(head == nullptr)
                return true;
            else
                return false;
        }

        //getting the front head of the link
        Node* get_head() const
        {
            return head;
        }

        //getting the tail of the link
        Node* get_tail() const
        {
            Node *temp = head;
            if(temp == nullptr)
                return temp;
            else
            {
                while( temp -> next != nullptr )
                {
                    temp = temp->next;
                }
                return temp;
            }
        }

        //getting the size of link;
        int get_size() const
        {
            return size;
        }

        //push the data to the back of the tail of the link.
        void push_back(const T &inputItem)
        {
            Node *nowTail = this->get_tail();
            Node *newNode = new Node;
            nowTail->next = newNode;
            newNode -> last = nowTail;
            newNode->item = inputItem;
            newNode->next = nullptr;
            this->size++;
        }  

        //push the data to the front of the head of the link.
        void push_front(const T &inputItem)
        {
            Node * nowHead = this->get_head();
            Node *newNode = new Node;
            nowHead->last = newNode;
            newNode->next = nowHead;
            newNode->item = inputItem;
            newNode->last = nullptr;
            this->size++;
        }


        //index reference, just like the array
        //but different from the list.
        T& operator[](int k)
        {
            /*if(k>=size)
            {
                cout << "the index is larger than the size.\n";
                if( this->is_empty() )
                {
                    cout << "the link is empty.\n"
                         << "returning -1 \n";
                    return -1.0;
                }
                else
                {
                    cout << "returning the first element\n";
                    return head->item;
                }
            }

            if(k<0)
            {
                cout << "the index is lower than 0\n";
                cout << "returning -1\n";
                return -1.0;
            }
            */
            int nodeFound = 0;
            Node *temp = head;
            while(nodeFound < k)
            {
                temp = temp->next;
                nodeFound++;
            }
            return temp->item;
        }
        
        //getting the  index number of the first node containing the input-item
        int find_first_of_item(const T& inputItem) const
        {
            Node* temp = head;
            bool flag = false;
            int index = 0;
            while( temp!=nullptr  )
            {
                if(temp->item == inputItem)
                {
                    flag = true;
                    break;
                }

                temp = temp->next;
                index++;
            }

            if(flag == true)
            {
                return index;
            }
            else
                return -1;
        }

         //getting the index number of the last node containing the input-item
        int find_last_of_item(const T& inputItem) const
        {
            Node* temp = this->get_tail();
            bool flag = false;
            int index = size - 1;
            while( temp!=nullptr  )
            {
                if(temp->item == inputItem)
                {
                    flag = true;
                    break;
                }

                temp = temp->last;
                index--;
            }

            if(flag == true)
            {
                return index;
            }
            else
                return -1;
        }

        //self-defining the iterator for the linkb;
        typedef MyIterator<T> iterator;

        iterator begin()
        {
            
        }


        //delete the node according to the index number
        void delet(int k)
        {
            if( k>=size || k<0 )
            {
                cout << "Invalid index.\n";
            }

            if( k==0 )
            {
                Node *temp = head->next;
                head = temp;
                temp = temp->last;
                delete temp;
                head->last = nullptr;
                size--;
            }

            if( k == size-1 )
            {
                Node *temp = this->get_tail()->last;
                delete this->get_tail();
                temp->next = nullptr;
                size--;
            }

            else
            {
                Node *temp = head;
                int num_node = 0;
                while (num_node < k)
                {
                    temp = temp->next;
                    num_node++;
                }
                Node *tempLast = temp->last;
                Node *tempNext = temp->next;
                tempLast->next = tempNext;
                tempNext->last = tempLast;
                delete temp;
            }
        }
        //deleting the node according to the input-item
        void delet(T& inputItem)
        {
            int currentIndex = this->find_first_of_item(inputItem);
            while(currentIndex != -1)
            {
                delet(currentIndex);
                currentIndex = this->find_first_of_item(inputItem);
            }    
        }

        //destructor of the link;
        ~Linkb()
        {
            Node * temp = head;
            if(temp == nullptr)
                delete temp;
            
            while(temp -> next != nullptr)
            {
                temp = temp->next;
                delete temp->last;
            }
            delete temp;
        }
};

#endif