
#ifndef EDF_PROCESSOR
#define EDF_PROCESSOR


#include "Processor.h"
#include "PriQueue.h"
class EDF_Processor : public Processor
{
private:

	PriQueue<Process*> Ready;

public:

	EDF_Processor(ProcessSch* SchedulerPointer);
	void stateUpdate();
	virtual void AddProcess(Process*);
	Process* RemoveProcess();
	virtual void ScheduleAlgo(int time);
	void printMyReady(); //Prints Ready Queue
	~EDF_Processor();

};

#endif


