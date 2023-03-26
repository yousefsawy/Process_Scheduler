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
    virtual void AddProcess(Process* );
    virtual void ScheduleAlgo();
};

