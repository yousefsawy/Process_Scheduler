#include "ProcessSch.h"
#include "UI_Class.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

ProcessSch::ProcessSch()
{
	timestep = 1;
	FCFS = 0;
	SJF = 0;
	RR = 0;
	TS_RR = 0;
	RTF = 0;
	MAXW = 0;
	NumOfProcess = 0;
	TotalProcessors = 0;
	AllProcessors = nullptr;

	srand(time(0));
	
}

bool ProcessSch::InputF(void)
{
	string s = "test"; //File name
	ifstream InputFile(s + ".txt");

	if (!InputFile.is_open())
		return false;


	InputFile >> FCFS >> SJF >> RR >> TS_RR >> RTF >> MAXW >> NumOfProcess;
	TotalProcessors = FCFS + SJF + RR;

	//Declare Processors
	AllProcessors = new Processor*[TotalProcessors]; 
	int i = 0;
	for (; i < FCFS; i++)
	{
		AllProcessors[i] = new FCFS_Processor(this);
	}
	for (; i < FCFS+SJF; i++)
	{
		AllProcessors[i] = new SJF_Processor(this);
	}
	for (; i < TotalProcessors; i++)
	{
		AllProcessors[i] = new RR_Processor(this,TS_RR);
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

void ProcessSch::Simulate()
{
	InputF();
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

		for (int j = 0; j < TotalProcessors; j++)
		{
			ProcessorSim(*AllProcessors[j], timestep);
		}

		//ToDo: Stealing,Migration,Killing,Forking
		timestep++;
		//cout << timestep << endl;
	}
	OutputF();
}

void ProcessSch::ToReady(LinkedQueue<Process*>& List)
{
	Process* temp2 = nullptr;  //Temporary value to hold the data while transfer
	List.dequeue(temp2);
	int MinExp = INT_MAX;
	int temp, list;
	//ToDo: Enqueque data to suitable processor using scheduling algorithm

	for (int i = 0; i < TotalProcessors; i++)
	{
		if (AllProcessors[i]->getExpectedFinishTime() <= MinExp)
		{
			MinExp = AllProcessors[i]->getExpectedFinishTime();
			temp = i;
		}
	}
	AllProcessors[temp]->AddProcess(temp2);

}

void ProcessSch::ProcessorSim(Processor& p, int time)
{
	p.ScheduleAlgo(time);
	Process* tempTer = p.RequestTerminated();
	Process* tempBlk = p.RequestBlocked();
	if (tempTer)
	{
		tempTer->setTT(time + 1);
		Terminated.enqueue(tempTer);
	}
	if (tempBlk)
	{
		Blocked.enqueue(tempBlk);
	}
}

bool ProcessSch::AreIdle()
{
	for (int j = 0; j < TotalProcessors; j++)
	{
		if (!AllProcessors[j]->isIdle())
		{
			return false;
		}
	}
	return true;
}

void ProcessSch::PrintRDY() {

	for (int i = 0; i < TotalProcessors; i++) {

		AllProcessors[i]->printMyReady();
		cout << endl;

	}

}

void ProcessSch::PrintBLK() {

	cout << Blocked.getCount() << " BLK: ";
	Blocked.print();
	cout << endl;

}

int ProcessSch::getNumRunning() const 
{
	int count = 0;

	for (int i = 0; i < TotalProcessors; i++) {

		if (AllProcessors[i]->isRunning()) {

			count++;

		}

	}

	return count;
}

void ProcessSch::PrintRun() 
{
	int NumRun = getNumRunning();
	int x = 1;

	cout << NumRun << " RUN: ";
	for (int i = 0; i < TotalProcessors; i++) {

		if (AllProcessors[i]->isRunning()) {

			AllProcessors[i]->printRunning();

			if (x != NumRun) {
				cout << ", ";
			}
			x++;

		}

	}

	cout << endl;

}

void ProcessSch::PrintTRM() {

	cout << Terminated.getCount() << " TRM: ";
	Terminated.print();
	cout << endl;

}

void ProcessSch::AddTerminated(Process*tempPtr) {

	if (!tempPtr)
		return;

	tempPtr->setTT(timestep + 1);
	Terminated.enqueue(tempPtr);
	//std::cout << "here";

}

void ProcessSch::AddBlocked(Process* tempPtr) {

	if (!tempPtr)
		return;

	Blocked.enqueue(tempPtr);

}

void ProcessSch::SignalKill(int ID)
{
	for (int i = 0; i < FCFS; i++)
	{
		if (AllProcessors[i]->KillSignal(ID))
			return;
	}
	
}

ProcessSch::~ProcessSch() {

	for (int i = 0; i < TotalProcessors; i++) {

		delete AllProcessors[i];

	}

	delete[] AllProcessors;

	Process* temp;

	while (!Terminated.isEmpty()) {

		Terminated.dequeue(temp);
		delete temp;

	}

}