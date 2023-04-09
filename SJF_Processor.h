#ifndef SJF_PROCESSOR
#define SJF_PROCESSOR

#include"Processor.h"
#include"PriQueue.h"

class SJF_Processor :public Processor {

private:

	PriQueue<Process*> Ready;

public:

	SJF_Processor();
	void stateUpdate();
	virtual void AddProcess(Process*);
	virtual void ScheduleAlgo();
	~SJF_Processor();

};

#endif