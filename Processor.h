#ifndef PROCESSOR_H
#define PROCESSOR_H

#include"DEFS.h"
#include"Process.h"

class ProcessSch;

class Processor {

protected:

	State currentState; //Processor current state
	int expectedFinishTime; //Expected time to finish all process
	Process* running; //Running process
	Process* Terminated; //Terminated process
	Process* Blocked; //Blocked process
	int BusyT, IdealT;
	int ID; // ID of processor;
	static int counter; // Counter to assign ID for each processor
	ProcessSch* SchPtr; //Scheduler Pointer
	int MaxW;
	int RTF;

public:

	Processor(ProcessSch* SchPtr, int MaxW, int RTF); //Constructor
	virtual void AddProcess(Process*) = 0; //Adds Process to Processor 
	virtual Process* RemoveProcess() = 0;
	bool isIdle() const; //Returns true if the processor has no processes
	virtual void stateUpdate() = 0; //Updates the state of processor
	int getExpectedFinishTime() const; //Returns expected time to finish all process
	int pUtil() const;
	int getBusy() const;
	virtual void ScheduleAlgo(int time) = 0; 
	bool isRunning() const; //Does the Processor have a running process
	void printRunning(); //Print the PID of running process
	int getID() const; //Returns ID of processor
	void setSchPtr(ProcessSch*); //Sets the Schduler pointer
	virtual void printMyReady()=0; //Prints the ready queue
	Process* RequestBlocked();
	Process* RequestTerminated();
	Process* getRun();
	virtual bool MigrateFCFS(int);
	virtual int Find(int); //Returns the index of the Process in the RDY from PID
	virtual bool KillSignal(int) { return false; }; //Kills the Signal
	virtual ~Processor(); //Destructor

};

#endif