#ifndef PROCESSOR_H
#define PROCESSOR_H

#include"DEFS.h"
#include"Process.h"

class Processor {

protected:

	State currentState; //Processor current state
	int expectedFinishTime; //Expected time to finish all process
	Process* running; //Running process
	Process* Terminated; //Terminated process
	Process* Blocked; //Blocked process
public:

	Processor(); //Constructor
	virtual void AddProcess(Process*) = 0; //Adds Process to Processor 
	bool isIdle() const; //Returns true if the processor has no processes
	virtual void stateUpdate() = 0;
	int getExpectedFinishTime() const; //Returns expected time to finish all process
	virtual void ScheduleAlgo(int time) = 0; 
	Process* RequestBlocked();
	Process* RequestTerminated();
	Process* getRun();
	~Processor(); //Destructor
	
	
};

#endif