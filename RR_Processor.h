#ifndef RR_PROCESSOR_H
#define RR_PROCESSOR_H

#include"LinkedQueue.h"
#include"Process.h"
#include"Processor.h"

class RR_Processor :public Processor {

private:

	int timeSlice;
	int currentTimeSlice;
	LinkedQueue<Process*> Ready;

public:

	RR_Processor(); //Constructor
	void stateUpdate(); //Updates processor state
	void AddProcess(Process*); //Adds process to ready queue "RDY"
	void ScheduleAlgo(); //Execute process
	void setTimeSlice(int t);
	~RR_Processor(); //Destructor

};

#endif