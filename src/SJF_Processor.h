#ifndef SJF_PROCESSOR_H
#define SJF_PROCESSOR_H

#include"Processor.h"
#include"PriQueue.h"

class SJF_Processor :public Processor {

private:

	PriQueue<Process*> Ready;

public:

	SJF_Processor(ProcessSch* SchedulerPointer, int MaxW, int RTF);
	void stateUpdate(bool);
	virtual void AddProcess(Process*);
	Process* RemoveProcess();
	virtual void ScheduleAlgo(int time);
	void printMyReady(); //Prints Ready Queue
	bool OverHeated();
	~SJF_Processor();

};

#endif