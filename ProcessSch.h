#pragma once
#include "LinkedQueue.h"
#include "Process.h"
#include "Processor.h"
#include "FCFS_Processor.h"

class ProcessSch
{
private:
	int timestep;
	int FCFS, SJF, RR; //Number of Processors of each type (FCFS, SJF, RR)
	int TS_RR; //Time slice for RR
	int RTF, MAXW; //Process Migration related
	LinkedQueue<Process> Processes; //List of processes
	LinkedQueue<Process*> New;  //Recieves all process from file
	LinkedQueue<Process*> Blocked;  //Contains blocked processes
	LinkedQueue<Process*> Terminated;  //Contains terminated processes
	FCFS_Processor* FCFSList; //List of FCFS processors
	// SJF_Processor* SJFList; //List of SJF processors
	// RR_Processor* RRList; //List of RR processors
	Processor* AllProcessors[3] = {FCFSList,/*SJFList,RRList*/};
public:
	ProcessSch();
	void Simulate();
	bool InputF(void);
	void NewToReady();
	~ProcessSch();
};

