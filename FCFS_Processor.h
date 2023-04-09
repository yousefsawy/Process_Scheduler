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
    virtual void TerminateProcess(Process*); //TODO: Terminate process from middle of list or RUN
    virtual Process* GetProcess(int PID); //TODO: RETURN Process* using PID from list or RUN
};

