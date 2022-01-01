#ifndef BACKTRACK
#define BACKTRACK
#include "Application.h"
/*
In this headfile, the class of BackTrack is universal.
In the specific occasions, 
we can write specific try_to_solve() function
*/
class BackTrack
{
    public:
        /*
        constructor using app to initialize this BackTrack object
        */
        BackTrack(const Application& app);

        /*
        CORE FUNCTION FOR THE BACKTRACK PURPOSE.
        Try to find a way out.if successful, return true.
        */
        bool try_to_solve(Position Pos); 

    protected:
        
        //the specific application
        Application app;

};//the class of BackTrack

#endif