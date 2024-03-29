#ifndef FCFS_PROCESSOR_H
#define FCFS_PROCESSOR_H

#include "Processor.h"
#include "ModifiedQueue.h"


class FCFS_Processor : public Processor
{
private:

    ModifiedQueue<Process*> Ready;
    const int ForkingP;

public:

    FCFS_Processor(ProcessSch* SchedulerPointer,int FP, int MaxW, int RTF);
    void stateUpdate(bool);
    virtual void AddProcess(Process*);
    Process* RemoveProcess();
    virtual void ScheduleAlgo(int time);
    void Forking(int time);
    void printMyReady(); //Prints Ready Queue
    virtual bool KillSignal(int);
    virtual int Find(int);
    virtual bool Migrate(int);
    bool OverHeated();
    ~FCFS_Processor();

};

#endif