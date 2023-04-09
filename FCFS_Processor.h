#pragma once
#include "Processor.h"
#include "LinkedQueue.h"


class FCFS_Processor :
    public Processor
{
private:
    LinkedQueue<Process*> Ready;
public:
    FCFS_Processor();
    void stateUpdate();
    virtual void AddProcess(Process*);
    virtual void ScheduleAlgo();
};

