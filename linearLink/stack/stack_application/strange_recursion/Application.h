#ifndef APPLICATION
#define APPLICATION
#include <iostream>
#include "Position.cpp"
using namespace std;
/*
Describe a application that requires recursion and backtrack
It is a only general one, the detail in the body of the function 
is required to be written in other cpp file
*/

class Application
{
    /*
    output the circumstance of a state in the application.
    */
    friend ostream& operator << (ostream& out , Application& app);
    
    public:
        /*
        using some input to generate the initial state and
        -return a position object.
        */
        Position generate_initial_state();
        
        /*
        If the position is on the way to the destination,return true
        And so and so forth.
        */
        bool valid(const Position &Pos) const; 

        /*
        recording the position(if this is valid)
        (maybe) by changing one of its flag.
        */
        void record(const Position &Pos);  

        /*
        If the position is the destination,return true
        And so and so forth.
        */
        bool done(const Position &Pos) const;

        /*
        recording the position that is not on the way to the destination
        */
        void undo(const Position &Pos); 

        /*
        this Iterator points at the specific state 
        and can change to the next state simply by++
        */

        class Iterator
        {
            public:
                
                /*
                default constructor
                */
                Iterator();
                
                /*
                constructor with the argument of a position
                */
                Iterator( Position Pos);

                //override for reassignment
                Iterator &operator=(const Iterator &itr);
                
                /*
                iterator++ to make it go upwards
                */       
                void upward();

                /*
                iterator++ to make it go downwards
                */       
                void downward();

                /*
                iterator++ to make it go westwards
                */       
                void westward();

                /*
                iterator++ to make it go eastwards
                */       
                void eastward();


                /*
                iterator-- to make it go upwards back
                */       
                Iterator back_upward();

                /*
                iterator-- to make it go downwards back
                */       
                Iterator back_downward();

                /*
                iterator-- to make it go westwards back
                */       
                Iterator back_westward();

                /*
                iterator-- to make it go eastwards back
                */       
                Iterator back_eastward();

                /*
                getting the position of the iterator
                */
                Position get_pos() const;

                /*
                checking whether the position 
                of the state has reached the end. 
                */
                bool at_end() const;

                /*
                go back to where it comes from
                (according to the element fromDiretion)
                */
                void go_back();

                /*destructor
                needed because I used a new command 
                to get the posPtr pointer  
                */
                ~Iterator();

            protected:
                Position* posPtr;

        };//the class of Iterator

};//the class of Application

#endif