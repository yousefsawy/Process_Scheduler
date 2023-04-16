#ifndef RR_PROCESSOR_H
#define RR_PROCESSOR_H

#include"LinkedQueue.h"
#include"Process.h"
#include"Processor.h"

class RR_Processor :public Processor {

private:

	const int timeSlice;
	int currentTimeSlice;
	LinkedQueue<Process*> Ready;

public:
	RR_Processor(ProcessSch* SchedulerPointer,int TS);
	//RR_Processor(); //Constructor
	void stateUpdate(); //Updates processor state
	void AddProcess(Process*); //Adds process to ready queue "RDY"
	void ScheduleAlgo(int time); //Execute process
	//void setTimeSlice(int t);
	void printMyReady(); //Prints Ready Queue
	~RR_Processor(); //Destructor

};

#endif