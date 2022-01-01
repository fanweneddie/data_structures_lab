#ifndef STATICLINK
#define STATICLINK

const int MAX_SIZE = 20;
/* THE DECLARATION OF THE STATIC LINK 
it is based on the array, so don't need a ptr to get the position.
*/
template <class T>
class StaticLink
{
    public:
        struct Node
        {
            int cursor;
            T data;
        };

        int size;
        Node *head;

    public:
        //two constructors,and the backup space is  initialized 
        StaticLink()
        {
            head = new Node[MAX_SIZE];
            size = 0;
            //INITIALIZING THE BACKUP SPACE.
            for (int i = 0; i < MAX_SIZE - 1;++i)
                head[i].cursor = i + 1;
            head[MAX_SIZE - 1].cursor = 0;
        }

        //getting the value of the members in the static link.
        int get_size() const { return size; }
        Node *get_head() const { return head; }

        // the malloc function will return the index that the head points to. 
        int malloc_space()
        {
            int cur = head[0].cursor;
            if( cur != 0 )
                head[0].cursor = head[cur].cursor;
            return cur;
        }
        // recycle the space with index k into the backup place.
        void free_space(int k)
        {
            head[k].cursor = head[0].cursor;
            head[0].cursor = k;
        }
        
        int locate_element(const T &element) const
        {
            int cur = head[0].cursor;
            while( cur!=0 && head[cur].data != element)
            {
                cur = head[cur].cursor;
            }
            return cur;
        }        

        ~StaticLink()
        {
            delete head;
        }

        class Iterator
        {
            private:
                Node *ptr;
            public:
                Iterator();
                Iterator(Node *pointer);
                bool operator==(const Iterator &it);
                bool operator!=(const Iterator &it);
                Iterator &operator++();
                Iterator operator++(int);
                Node *get_ptr() const;
                T &operator*();
        };
};


        
        
#endif




