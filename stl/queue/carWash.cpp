#include "carWash.h"
#include <string>
#include <iostream>
using namespace std;

//means there is now no car being washed
const int CarWash::INFINITY = 5000;

const int CarWash::MAX_SIZE = 5;
const int CarWash::WASH_TIME = 10;

//constructor
//And the objects of Car and queue<Car> are
//-constructed automatically.
CarWash::CarWash()
{
    currentTime = 0;
    nextDepartureTime = INFINITY;
    numOfCars = 0;
    sumOfWaitingTime = 0;
}

//process the car that has arrived
//(both need to line up and need not )
void CarWash::processArrival(int nextArrivalTime)
{
    const string OVERFLOW = "CAR OVERFLOW.";

    //if the queue is full, the coming car 
    //-have to turn around and go away.
    if( carQueue.size() == MAX_SIZE )
    {
        cout << OVERFLOW << endl;
        return;
    }

    numOfCars++;

    //no need to wait in the queue,
    //so we don't need to record its arrivalTime
    //,because its waiting time is 0.
    //Just changing the next departure time is fine.
    if( nextDepartureTime == INFINITY )
    {
        nextDepartureTime = nextArrivalTime + WASH_TIME;
    }

    //need to wait in queue
    //so we push it into the carQueue to record 
    //-its arrivalTime
    else
    {
        Car newCar(nextArrivalTime);
        carQueue.push(newCar);
    }
} 

//process the car that has finished being washed.
//And it can calculate the waiting time of the car 
//-that has finished waiting.
void CarWash::processDeparture()
{
    //don't forget to calculate the waiting time of the leaving car
    int waitingTime;
    cout << "DEPARTURE TIME = " << nextDepartureTime << endl;
    currentTime = nextDepartureTime;

    // there are some cars in the queue
    if( !carQueue.empty() )
    {
        Car leavingCar = carQueue.front();
        waitingTime = currentTime - leavingCar.get_arrivalTime();
        sumOfWaitingTime += waitingTime;
        nextDepartureTime = currentTime + WASH_TIME;
        carQueue.pop();
    }
    //there is no car in the queue, meaning the last car has been washed.
    //don't need to calculate the washTime
    //because the waiting time is the most important.
    else
    {
        nextDepartureTime = INFINITY;
    }
}

// integrate both of the above functions and control 
//-the main process of this game
void CarWash::stimulate()
{
    const string INPUT_PROMPT 
    = "PLEASE INPUT THE NEXT ARRIVAL TIME, THE SENTINIEL IS ";
    const int SENTINIEL = 999;
    int nextArrivalTime;

    cout << INPUT_PROMPT << SENTINIEL << endl;
    cin >> nextArrivalTime;

    //continue inputing the arrival time which 
    //-shows cars coming.
    while( nextArrivalTime != SENTINIEL )
    {
        
        //if the next arrival time is before the next departure time, 
        //we just process its arrival.
        //Don't forget to continue the input in a loop
        if( nextArrivalTime < nextDepartureTime )
        {
            processArrival(nextArrivalTime);
            cout << INPUT_PROMPT << SENTINIEL << endl;
            cin >> nextArrivalTime;
        }

        //if the next arrival time is after the next departure time, 
        //first we need to process the departure of the car that has been washed,
        //then we can process its arrival.
        //Don't forget to continue the input in a loop
        else
        {
            processDeparture();
            processArrival(nextArrivalTime);
            cout << INPUT_PROMPT << SENTINIEL << endl;
            cin >> nextArrivalTime;
        }         
    }
    
    //dealing with the remaining cars
    while( nextDepartureTime < INFINITY)
    {
        processDeparture();
    }
}

// output the result,showing the number of cars and 
//- the average waiting time.
void CarWash::print_result() const
{
    const string NO_CAR_MESSAGE = " THERE IS NO CAR IN THE CAR WASH.";
    if( numOfCars == 0 )
        cout << NO_CAR_MESSAGE << endl;
    else
    {
        cout << "THERE ARE " << numOfCars << " CARS WASHED." << endl;
        cout << "NUMBER OF CARS = " << numOfCars << endl;
        cout << "SUM OF WAITING TIME = " << sumOfWaitingTime << endl;
        cout << "THE AVERAGE WAITING TIME IS "
             << (double)sumOfWaitingTime / numOfCars << endl;
    }
}