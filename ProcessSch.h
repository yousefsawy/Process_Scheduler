#pragma once

#include "LinkedQueue.h"
#include "Process.h"
#include "Processor.h"
#include "FCFS_Processor.h"
#include "RR_Processor.h"
#include "SJF_Processor.h"

class ProcessSch
{
private:

	int timestep; 
	int FCFS, SJF, RR; //Number of Processors of each type (FCFS, SJF, RR)
	int TS_RR; //Time slice for RR
	int RTF, MAXW; //Process Migration related
	int NumOfProcess; //Number of process
	int TotalProcessors; //Total number of processors
	LinkedQueue<Process*> New;  //Recieves all process from file
	LinkedQueue<Process*> Blocked;  //Contains blocked processes
	LinkedQueue<Process*> Terminated;  //Contains terminated processes
	Processor** AllProcessors; //List of all processors

public:

	ProcessSch();
	bool InputF(void);
	void OutputF();
	void ToReadyph1(LinkedQueue<Process*>& List,int& index);
	void Simulateph1();
	void ProcessorSimph1(Processor& p);
	bool AreIdle();
	int getNumRunning() const; // returns number of processors having a running process
	void PrintRDY(); //Prints RDY of each processor
	void PrintBLK(); //Prints Blocked List
	void PrintRun(); //Prints RUN of each processor
	void PrintTRM(); //Prints Terminated List
	void AddTerminated(Process*); //Adds a process to terminated
	void AddBlocked(Process*); //Adds a process to blocked
	~ProcessSch();

};