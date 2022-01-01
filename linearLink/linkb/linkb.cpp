#include "linkb.h"

template <class T>
Linkb::Linkb(int maxSize = 0)
{
            if(maxSize == 0)
            {
                head->next = nullptr;
                head->last = nullptr;
                head = nullptr;
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

template <class T>
Node*Linkb::create()
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