#ifndef PROCESSOR_H
#define PROCESSOR_H

#include"DEFS.h"
#include"Process.h"

class Processor {

protected:

	State currentState; //Processor current state
	int expectedFinishTime; //Expected time to finish all process
	Process* running; //Running process

public:

	Processor(); //Constructor
	bool isIdle() const; //Returns true if the processor has no processes
	int getExpectedFinishTime() const; //Returns expected time to finish all process
	virtual void ScheduleAlgo() = 0;
	Process* RequestBlocked(); //
	Process* RequestTerminated();
	~Processor(); //Destructor

};

#endif