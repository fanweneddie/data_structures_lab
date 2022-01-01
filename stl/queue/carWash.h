#ifndef CARWASH
#define CARWASH
#include <queue>
using namespace std;

class CarWash
{
    //A first declaration of the class of Car 
    //in order to avoid undeclaration
    public:
        class Car;

    protected:
        int currentTime;
        int nextDepartureTime;

        //the number of cars includes the cars that goes to be washed 
        //directly with lining up.
        int numOfCars; 

        //attention: we only focus on the waiting time,
        //not including the washing time of each car. 
        int sumOfWaitingTime;

        //building a queue that contains cars
        queue<Car> carQueue;

        // no car is being washed
        const static int INFINITY;

        const static int MAX_SIZE;
        const static int WASH_TIME;

    public:
        //building a class of car, and now
        //-it only has a element of arrivalTime.
        class Car
        {
            protected:
                int arrivalTime;

            public:
                Car(int nextArrivalTime)
                {
                    arrivalTime = nextArrivalTime;
                }

                int get_arrivalTime() const
                {
                    return arrivalTime;
                }
        };

        CarWash();
        
        //process the car that has arrived
        //(both need to line up and need not )
        void processArrival(int nextArrivalTime);
        
        //process the car that has finished being washed.
        //And it can calculate the waiting time of the car 
        //-that has finished waiting.
        void processDeparture();

        // integrate both of the above functions and control 
        //-the main process of this game
        void stimulate();

        // output the result,showing the number of cars and 
        //- the average waiting time.
        void print_result() const;
};

#endif