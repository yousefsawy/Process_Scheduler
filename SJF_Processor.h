#ifndef SJF_PROCESSOR
#define SJF_PROCESSOR

#include"Processor.h"
#include"PriQueue.h"

class SJF_Processor :public Processor {

private:

	PriQueue<Process*> Ready;

public:

	SJF_Processor(ProcessSch* SchedulerPointer);
	void stateUpdate();
	virtual void AddProcess(Process*);
	Process* RemoveProcess();
	virtual void ScheduleAlgo(int time);
	void printMyReady(); //Prints Ready Queue
	~SJF_Processor();

};

#endif