#pragma once

#include "LinkedQueue.h"
#include "Process.h"
#include "Processor.h"
#include "FCFS_Processor.h"
#include "RR_Processor.h"
#include "SJF_Processor.h"
#include "EDF_Processor.h"

class ProcessSch
{
private:

	int timestep; 
	int FCFS, SJF, EDF, RR; //Number of Processors of each type (FCFS, SJF, EDF, RR)
	int TS_RR; //Time slice for RR
	int RTF, MAXW; //Process Migration related
	int STL, FP; // Steal limit and Forking Probabiltity
	int NumOfProcess; //Number of process
	int TotalProcessors; //Total number of processors
	int countKill; //number of processes killed sucessfully
	int countSteal; //number of processes stolen
	int CountRTF, CountMaxW; //number of processes migrated
	LinkedQueue<Process*> New;  //Recieves all process from file
	LinkedQueue<Process*> Blocked;  //Contains blocked processes
	LinkedQueue<Process*> Terminated;  //Contains terminated processes
	LinkedQueue<SigKill*> Kill; //list of kill signals
	Processor** AllProcessors; //List of all processors

public:

	ProcessSch();
	bool InputF(void);
	void OutputF();
	void ToReady(LinkedQueue<Process*>& List);
	void ToReadyForking(Process* Process);
	void Stealing();
	void Simulate();
	void ProcessorSim(Processor& p,int);
	bool AreIdle();
	int getNumRunning() const; // returns number of processors having a running process
	void PrintRDY(); //Prints RDY of each processor
	void PrintBLK(); //Prints Blocked List
	void PrintRun(); //Prints RUN of each processor
	void PrintTRM(); //Prints Terminated List
	void AddTerminated(Process*); //Adds a process to terminated
	void AddBlocked(Process*); //Adds a process to blocked
	void SignalKill(int);
	bool MigrateToRR(Process*);
	bool MigrateToSJF(Process*);
	~ProcessSch();

};