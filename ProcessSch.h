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
	int TotalPro; //Total number of processors
	LinkedQueue<Process*> New;  //Recieves all process from file
	LinkedQueue<Process*> Blocked;  //Contains blocked processes
	LinkedQueue<Process*> Terminated;  //Contains terminated processes
	FCFS_Processor* FCFSList; //List of FCFS processors
	SJF_Processor* SJFList; //List of SJF processors
	RR_Processor* RRList; //List of RR processors
public:
	ProcessSch();
	void Simulate();
	bool InputF(void);
	void OutputF();
	void ToReady(LinkedQueue<Process*>& List);
	void ToReadyph1(LinkedQueue<Process*>& List,int& index);
	void Simulateph1();
	void ProcessorSimph1(Processor& p);
	void ProcessorSim(Processor& p,int time);
	bool AreIdle();
	~ProcessSch();
	int getNumRunning() const; // returns number of processors having a running process
	void PrintRDY(); //Prints RDY of each processor
	void PrintBLK(); //Prints Blocked List
	void PrintRun(); //Prints RUN of each processor
	void PrintTRM(); //Prints Terminated List
	void AddTerminated(Process*); //Adds a process to terminated
	void AddBlocked(Process*); //Adds a process to blocked
};

