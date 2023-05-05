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
	countKill = 0;
	countSteal = 0;
	srand(time(0));

}

bool ProcessSch::InputF(void)
{
	string s = "Input"; //File name
	ifstream InputFile(s + ".txt");

	if (!InputFile.is_open())
		return false;


	InputFile >> FCFS >> SJF >> EDF >> RR >> TS_RR >> RTF >> MAXW >>STL>>FP>> NumOfProcess;
	TotalProcessors = FCFS + SJF + EDF + RR;

	//Declare Processors
	AllProcessors = new Processor * [TotalProcessors];
	int i = 0;
	for (; i < FCFS; i++)
	{
		AllProcessors[i] = new FCFS_Processor(this,FP, MAXW, RTF);
	}
	for (; i < FCFS + SJF; i++)
	{
		AllProcessors[i] = new SJF_Processor(this, MAXW, RTF);
	}
	for (; i < FCFS + SJF + EDF; i++)
	{
		AllProcessors[i] = new EDF_Processor(this, MAXW, RTF);
	}
	for (; i < TotalProcessors; i++)
	{
		AllProcessors[i] = new RR_Processor(this, TS_RR, MAXW, RTF);
	}

	for (int i = 0; i < NumOfProcess; i++)
	{
		int AT, PID, CT, ED,N; // Arrival Time, Process ID, CPU Time,Earliest deadline, Number of process requests  I/O
		InputFile >> AT >> PID >> CT >> ED >> N;

		//TODO: Create a Process (PriNode or Node then add it to the processor)
		Process* tempProcess = new Process(AT, CT, ED, N);
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
	int sigKillnum, time, PID;
	InputFile >> sigKillnum;
	for (int i = 0; i < sigKillnum; i++)
	{
		InputFile >> time >> PID;
		SigKill* temp = new SigKill;
		temp->time = time;
		temp->PID = PID;
		Kill.enqueue(temp);
	}
	return true;
}

void ProcessSch::OutputF()
{
	string s = "Output"; //File name
	ofstream OutputFile(s + ".txt");

	if (!OutputFile.is_open())
		return;
	NumOfProcess = Process::getCount();
	Process* temp;
	OutputFile << "TT" << "\t" << "PID" << "\t" << "AT" << "\t" << "CT" << "\t" << "IO_D" << "\t" << "WT" << "\t" << "RT" << "\t" << "TRT" << endl;
	int SumWT = 0,SumRT=0,countED=0.,SumTRT=0,countF=0;
	while (Terminated.dequeue(temp))
	{
		temp->PrintInfo(OutputFile);
		SumWT+=temp->getWT();
		SumRT += temp->getRT();
		SumTRT += temp->getTRT();
		if (temp->getforked())
		{
			countF++;
		}
		if (temp->getTT() < temp->getED())
		{
			countED++;
		}
		delete temp;
	}
	int AvgWT = SumWT / NumOfProcess;
	int AvgRT = SumRT / NumOfProcess;
	int AvgTRT = SumTRT / NumOfProcess;


	OutputFile << "Processes: " << NumOfProcess << endl<<endl;
	OutputFile << "Avg WT=" << AvgWT << ",		Avg RT=" << AvgRT << ",		Avg TRT=" << AvgTRT << endl;
	OutputFile << "Migration:		" <<"RTF = "<< "%		MaxW = " << "% \n";
	OutputFile << "Work Steal: " << countSteal*100 / NumOfProcess << "% \n";
	OutputFile << "Forked Process: " << countF * 100 / NumOfProcess << "% \n";
	OutputFile << "Killed Process: " << countKill*100 / NumOfProcess << "% \n";
	OutputFile << "Before Deadline: " << countED * 100 / NumOfProcess << "% \n";
	OutputFile << "\nProcessors: " << TotalProcessors << " [" << FCFS << " FCFS, " << SJF << " SJF, " << EDF <<" EDF, " << RR << " RR]\n";
	OutputFile << "Processor Load\n";
	for (int i = 0; i < TotalProcessors; i++)
	{
		OutputFile << 'p' << i + 1 << '=' << round((float)(AllProcessors[i]->getBusy()*100)/(SumTRT-SumWT))<< "%	";
	}
	OutputFile << "\n\nProcessor Utilization\n";
	int SumUtil = 0;
	for (int i = 0; i < TotalProcessors; i++)
	{
		int temp = AllProcessors[i]->pUtil();
		OutputFile << 'p' << i + 1 << '=' << temp << "%\t";
		SumUtil += temp;
	}
	OutputFile << "\n\nAvg utilization = " << SumUtil / TotalProcessors << "% \n";
}

void ProcessSch::Simulate()
{
	InputF();
	UI_Class UIC(this);
	while (!(New.isEmpty() && Blocked.isEmpty() && AreIdle()))
	{
		//Process Stealing
		if (timestep % STL == 0)
		{
			Stealing();
		}

		//Process killing
		int ID_KillSig;
		SigKill* temp3 = nullptr;
		Kill.peek(temp3);
		if (temp3 && temp3->time == timestep)
		{
			ID_KillSig = temp3->PID;
			SignalKill(ID_KillSig);
			Kill.dequeue(temp3);
			delete temp3;
		}

		//check if process in Run goes to blocked or terminatted
		//if processor Run is empty adds one from ready queue
		for (int j = 0; j < TotalProcessors; j++)
		{
			ProcessorSim(*AllProcessors[j], timestep);
		}

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


		//ToDo:Migration
		timestep++;
		UIC.ExecuteUI();
	}
	OutputF();
}

void ProcessSch::ToReady(LinkedQueue<Process*>& List)
{
	Process* temp2 = nullptr;  //Temporary value to hold the data while transfer
	List.dequeue(temp2);
	int MinExp = INT_MAX;
	int temp;
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

void ProcessSch::ToReadyForking(Process* Process)
{
	int MinExp = INT_MAX;
	int temp;
	//ToDo: Enqueque data to suitable processor using scheduling algorithm

	for (int i = 0; i < FCFS; i++)
	{
		if (AllProcessors[i]->getExpectedFinishTime() <= MinExp)
		{
			MinExp = AllProcessors[i]->getExpectedFinishTime();
			temp = i;
		}
	}
	AllProcessors[temp]->AddProcess(Process);
}

void ProcessSch::Stealing()
{
	int MinExp = INT_MAX,MaxExp=0;
	int Min=0,Max=0;

	for (int i = 0; i < TotalProcessors; i++)
	{
		if (AllProcessors[i]->getExpectedFinishTime() <= MinExp)
		{
			MinExp = AllProcessors[i]->getExpectedFinishTime();
			Min = i;
		}
		if (AllProcessors[i]->getExpectedFinishTime() >= MaxExp)
		{
			MaxExp = AllProcessors[i]->getExpectedFinishTime();
			Max = i;
		}
	}
	while (((float)(MaxExp - MinExp) / MaxExp) > 0.4)
	{
		Process* temp = nullptr;
		temp=AllProcessors[Max]->RemoveProcess();
		if (temp == nullptr)
			break;
		AllProcessors[Min]->AddProcess(temp);
		MaxExp = AllProcessors[Max]->getExpectedFinishTime();
		MinExp = AllProcessors[Min]->getExpectedFinishTime();
		countSteal++;
	}
}

void ProcessSch::ProcessorSim(Processor& p, int time)
{
	p.ScheduleAlgo(time);
	Process* tempTer = p.RequestTerminated();
	Process* tempBlk = p.RequestBlocked();
	if (tempTer)
	{
		AddTerminated(tempTer);
	}
	if (tempBlk)
	{
		AddBlocked(tempBlk);
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

void ProcessSch::AddTerminated(Process* tempPtr) {

	if (!tempPtr)
		return;

	tempPtr->setTT(timestep);
	Terminated.enqueue(tempPtr);
	if (tempPtr->getLchild())
	{
		SignalKill(tempPtr->getLchild()->getPID());
	}
	if (tempPtr->getRchild())
	{
		SignalKill(tempPtr->getRchild()->getPID());
	}
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
		{
			countKill++;
			return;
		}
	}
}

bool ProcessSch::MigrateToRR(Process* Prcs)
{
	int MinExp = INT_MAX;
	int temp = -1;

	for (int i = FCFS + SJF + EDF; i < TotalProcessors; i++)
	{
		if (AllProcessors[i]->getExpectedFinishTime() <= MinExp)
		{
			MinExp = AllProcessors[i]->getExpectedFinishTime();
			temp = i;
		}
	}
	if (temp == -1)
		return false;
	AllProcessors[temp]->AddProcess(Prcs);
	return true;
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