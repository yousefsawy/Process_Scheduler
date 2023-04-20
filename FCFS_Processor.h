#pragma once

#include "Processor.h"
#include "ModifiedQueue.h"


class FCFS_Processor : public Processor
{
private:

    ModifiedQueue<Process*> Ready;

public:

    FCFS_Processor(ProcessSch* SchedulerPointer);
    void stateUpdate();
    virtual void AddProcess(Process*);
    Process* RemoveProcess();
    virtual void ScheduleAlgo(int time);
    void printMyReady(); //Prints Ready Queue
    virtual bool KillSignal(int);
    virtual int Find(int);
    ~FCFS_Processor();

};

