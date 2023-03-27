#include "ProcessSch.h"
#include <fstream> //Needed for the Input/Output function
using namespace std;



ProcessSch::ProcessSch()
{
	timestep = 0;
	InputF();
}

void ProcessSch::Simulate()
{
	while ( !New.isEmpty() && !Blocked.isEmpty() ) //TODO: while processor lists are empty loop
	{
		Process* temp1; //checks if AT first  process in New is equal to timestep
		New.peek(temp1);
		while (temp1->getAT() == timestep) //Puts data in the RDY queues of processors
		{
			NewToReady();
			New.peek(temp1);
		}
		//ToDO: check if process in Run goes to blocked or terminatted
		//ToDo: if processor Run is empty adds one from ready queue
		//ToDo: Stealing,Migration,Killing,Forking
		timestep++;
		//ToDo: interface mode action
	}
	//ToDo: Produce the output file
}

bool ProcessSch::InputF(void)
{
	string s = "test"; //File name
	ifstream InputFile(s + ".txt");

	if (!InputFile.is_open())
		return false;


	int NumOfProcess; //Number of process

	InputFile >> FCFS >> SJF >> RR >> TS_RR >> RTF >> MAXW >> NumOfProcess;

	//Declare Processors

	FCFSList = new FCFS_Processor[FCFS];
	//SJFList = new SJF_Processor[SJF];
	//RRList = new RR_Processor[RR];

	for (int i = 0; i < NumOfProcess; i++)
	{
		int AT, PID, CT, N; // Arrival Time, Process ID, CPU Time, Number of process requests  I/O
		InputFile >> AT >> PID >> CT >> N;

		//TODO: Create a Process (PriNode or Node then add it to the processor)
		Process* tempProcess = new Process(PID, AT, CT, N);
		//

		for (int j = 0; j < N; j++)
		{
			int IO_R, IO_D; // I/O Request time, I/O Duration time
			InputFile.ignore(2);
			InputFile >> IO_R;
			InputFile.ignore();
			InputFile >> IO_D;
			//TODO: Add I/O Request to Process
			tempProcess->AddRequest(IO_R, IO_D);

			InputFile.ignore();
		}

		Processes.enqueue(*tempProcess);  //Adds the process to processes list
		New.enqueue(tempProcess); //Adds the process to new list
	}
	return true;
}


void ProcessSch::NewToReady()
{
	Process* temp2;  //Temporary value to hold the data while transfer
	New.dequeue(temp2);
	//ToDo: Enquque data to suitable processor using scheduling algorithm
}

ProcessSch::~ProcessSch(){}