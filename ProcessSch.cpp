#include "ProcessSch.h"
#include <iostream>
#include <fstream> //Needed for the Input/Output function
using namespace std;



ProcessSch::ProcessSch()
{
	timestep = 0;
	InputF();
}

void ProcessSch::Simulate()
{
	while (!(New.isEmpty() && Blocked.isEmpty() && AreIdle())) //TODO: while processor lists are empty loop
	{
		Process* temp1; //checks if AT first  process in New is equal to timestep
		New.peek(temp1);
		while (temp1->getAT() == timestep && !New.isEmpty()) //Puts data in the RDY queues of processors
		{
			ToReady(New);
			New.peek(temp1);
		}


		Process* temp2 = nullptr;
		Blocked.peek(temp2); //checks if Blocked list first at each timestep
		if (temp2)
		{
			if (temp2->isIORequest())
			{
				temp2->IncrementIO_D();

			}
			else
			{
				ToReady(Blocked);
			}
		}

		//check if process in Run goes to blocked or terminatted
		//if processor Run is empty adds one from ready queue

		for (int j = 0; j < FCFS; j++)
		{
			ProcessorSim(FCFSList[j],timestep);
		}
		
		for (int j = 0; j < SJF; j++)
		{
			ProcessorSim(SJFList[j],timestep);
		}
		for (int j = 0; j < RR; j++) {
			ProcessorSim(RRList[j],timestep);
		}
		
		//ToDo: Stealing,Migration,Killing,Forking
		timestep++;
		//ToDo: interface mode action
		cout << timestep << endl;
	}
	//ToDo: Produce the output file
	OutputF();
}

bool ProcessSch::InputF(void)
{
	string s = "test"; //File name
	ifstream InputFile(s + ".txt");

	if (!InputFile.is_open())
		return false;


	InputFile >> FCFS >> SJF >> RR >> TS_RR >> RTF >> MAXW >> NumOfProcess;

	//Declare Processors

	FCFSList = new FCFS_Processor[FCFS];
	SJFList = new SJF_Processor[SJF];
	RRList = new RR_Processor[RR];
	for (int i = 0; i < RR; i++)
	{
		RRList[i].setTimeSlice(TS_RR);
	}

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
		New.enqueue(tempProcess); //Adds the process to new list
	}
	return true;
}

void ProcessSch::OutputF()
{
	string s = "test1"; //File name
	ofstream OutputFile(s + ".txt");

	if (!OutputFile.is_open())
		return;
	Process* temp;
	OutputFile << "TT" << "\t" << "PID" << "\t" << "AT" << "\t" << "CT" <<"\t" << "IO_D" << "\t"  << "WT" << "\t" << "RT" << "\t" << "TRT" << endl;
	while (Terminated.dequeue(temp))
	{
		temp->PrintInfo(OutputFile);
		delete temp;
	}
	OutputFile << "Processes: " << NumOfProcess << endl;


}


void ProcessSch::ToReady(LinkedQueue<Process*>& List)
{
	Process* temp2=nullptr;  //Temporary value to hold the data while transfer
	List.dequeue(temp2);
	int MinExp = INT_MAX;
	int temp,list;
	//ToDo: Enqueque data to suitable processor using scheduling algorithm
	for (int j = 0; j < FCFS; j++)
	{
		if (FCFSList[j].getExpectedFinishTime() <= MinExp)
		{
			MinExp = FCFSList[j].getExpectedFinishTime();
			temp = j;
			list = 1;
		}
	}
	for (int j = 0; j < SJF; j++)
	{
		if (SJFList[j].getExpectedFinishTime() <= MinExp)
		{
			MinExp = SJFList[j].getExpectedFinishTime();
			temp = j;
			list = 2;
		}
	}
	for (int j = 0; j < RR; j++)
	{
		if (RRList[j].getExpectedFinishTime() <= MinExp)
		{
			MinExp = RRList[j].getExpectedFinishTime();
			temp = j;
			list = 3;
		}
	}
	switch (list)
	{
	case 1:
		FCFSList[temp].AddProcess(temp2);
		break;
	case 2:
		SJFList[temp].AddProcess(temp2);
		break;
	case 3:
		RRList[temp].AddProcess(temp2);
		break;
	}
	
}


void ProcessSch::ProcessorSim(Processor& p,int time)
{
	p.ScheduleAlgo(time);
	Process* tempTer = p.RequestTerminated();
	Process* tempBlk = p.RequestBlocked();
	if (tempTer)
	{
		tempTer->setTT(time+1);
		Terminated.enqueue(tempTer);
	}
	if (tempBlk)
	{
		Blocked.enqueue(tempBlk);
	}
}

bool ProcessSch::AreIdle()
{
	for (int j = 0; j < FCFS; j++)
	{
		if (!FCFSList[j].isIdle())
		{
			return false;
		}
	}
	for (int j = 0; j < SJF; j++)
	{
		if (!SJFList[j].isIdle())
		{
			return false;
		}
	}
	for (int j = 0; j < RR; j++)
	{
		if (!RRList[j].isIdle())
		{
			return false;
		}

	}
	return true;
}




ProcessSch::~ProcessSch() {}