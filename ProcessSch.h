#pragma once
#include "LinkedQueue.h"
#include "Process.h"
//#include "Processor"

class ProcessSch
{
private:
	int timestep;
	LinkedQueue<Process> New;  //Recieves all process from file
	LinkedQueue<Process> Blocked;  //Contains blocked processes
	LinkedQueue<Process> Terminated;  //Contains terminated processes
	//Process* AllProcessors[3];
public:
	ProcessSch();
	void Simulate();
	bool InputF(void);
	void NewToReady();
	~ProcessSch();
};

