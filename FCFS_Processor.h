#pragma once
#include "Processor.h"
#include "ModifiedQueue.h"


class FCFS_Processor :
    public Processor
{
private:
    ModifiedQueue<Process*> Ready;
    int count; //Count of number of process (Used for random Kill)
public:
    FCFS_Processor(ProcessSch* SchedulerPointer);
    void stateUpdate();
    virtual void AddProcess(Process*);
    virtual void ScheduleAlgo(int time);
    void printMyReady(); //Prints Ready Queue
    void KillRandom();
};

