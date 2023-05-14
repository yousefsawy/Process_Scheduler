#include "FCFS_Processor.h"
#include "ProcessSch.h"


FCFS_Processor::FCFS_Processor(ProcessSch* SchedulerPointer, int FP, int MaxW, int RTF) :Processor(SchedulerPointer, MaxW, RTF), ForkingP(FP)
{
}

void FCFS_Processor::stateUpdate() {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
		IdealT++; //3ayzeen nsheel de
	}
	else {
		currentState = BUSY;
		BusyT++; //3ayzeen nsheel de
	}

}

void FCFS_Processor::printMyReady() {
	
	std::cout << "processor " << getID() << "[FCFS]: " << Ready.getCount() << " RDY: ";
	if (isOverHeated())
	{
		std::cout << "OVERHEATED!!!";
	}
	else
	{
		Ready.print();
	}
	

}

bool FCFS_Processor::KillSignal(int PID)
{
	if (running && running->getPID() == PID)
	{
		SchPtr->AddTerminated(running);
		expectedFinishTime -= running->getRemtime();
		running = nullptr;
	}
	else
	{
		int index = Find(PID);
		if (index == -1)
			return false;

		Process* temp = nullptr;
		Ready.deleteMid(index, temp);
		if (!temp)
			return false;

		SchPtr->AddTerminated(temp);
		expectedFinishTime -= temp->getRemtime();
	}
	stateUpdate();
	return true;
}

int FCFS_Processor::Find(int ID)
{
	ModifiedQueue<Process*> tempQ;
	Process* tempP;
	int i = 0;
	int n = -1;
	while (Ready.dequeue(tempP))
	{
		tempQ.enqueue(tempP);
		if (tempP->getPID() == ID)
			n = i;
		i++;
	}
	while (tempQ.dequeue(tempP))
	{
		Ready.enqueue(tempP);
	}
	return n;
}

bool FCFS_Processor::Migrate(int time)
{
	bool Migrated = false;
	int WaitingTime = time - running->getAT() - running->getRunT();
	if (WaitingTime > MaxW && !running->getIschild())
	{
		Migrated = SchPtr->MigrateToRR(running);
		if (Migrated)
		{
			expectedFinishTime -= running->getRemtime();
			running = nullptr;
			stateUpdate();
		}
	}
	return Migrated;
}

void FCFS_Processor::AddProcess(Process* NewPrcs)
{
	NewPrcs->setStatus(RDY);
	Ready.enqueue(NewPrcs);
	expectedFinishTime += NewPrcs->getRemtime();
	stateUpdate();
}

Process* FCFS_Processor::RemoveProcess() {
	Process* p = nullptr;
	Ready.peek(p);
	if (p && !p->getIschild())
	{
		Ready.dequeue(p);
		expectedFinishTime -= p->getRemtime();
	}
	else
	{
		p = nullptr;
	}
	stateUpdate();
	return p;

}

void FCFS_Processor::ScheduleAlgo(int time)
{

	if (currentState == IDLE) {
		IdealT++;
		return;
	}

	if (OverHeated()) {
		return;
	}
	
	if (running == nullptr)
	{
		
		Process* temp;
		Ready.peek(temp);
		if (temp->getAT() >= time) //Leeh?
		{
			return;
		}
		
		Ready.dequeue(running);
		running->setStatus(RUN);

		//Migration
		bool Mig = Migrate(time);
		if (Mig)
		{
			while (Mig)
			{
				if (currentState == IDLE)
					return;
				Ready.dequeue(running);
				Mig = Migrate(time);
			}
			return;
		}

	}
	if (running->getRunT() == 0)
	{
		running->setRT(time /*timestep*/);
	}
	running->IncrementRunT();
	expectedFinishTime--;
	currentState = BUSY;
	if (running->isTerminated())
	{
		Terminated = running;
		running = nullptr;
		Terminated->setStatus(TRM);
	}
	else if (running->isIORequest())
	{
		Blocked = running;
		running = nullptr;
		Blocked->setStatus(BLK);
	}
	else
	{
		Forking(time);
	}

	stateUpdate();

}

void FCFS_Processor::Forking(int time)
{
	if (!running->getforked())
	{

		Process* temp = nullptr;
		int rand1 = rand() % 100 + 1;
		if (rand1 <= ForkingP)
		{
			temp = new Process(time, running->getRemT(), INT_MAX,0, true);
			running->setLchild(temp);
			SchPtr->ToReadyForking(temp);
			temp = nullptr;
			running->Forked();
		}
		int rand2 = rand() % 100 + 1;
		if (rand2 <= ForkingP)
		{
			temp = new Process(time, running->getRemT(), INT_MAX,0, true);
			running->setRchild(temp);
			SchPtr->ToReadyForking(temp);
			temp = nullptr;
			running->Forked();
		}
	}
}

bool FCFS_Processor::OverHeated() {

	if (currentState == STOP) {

		stopTimesteps--;

		if (stopTimesteps == 0) {
			currentState = IDLE;
		}

		return true;

	}

	bool toSTOPState = rand() % 1;

	if (toSTOPState) {

		currentState = STOP;
		stopTimesteps = SchPtr->getn();
		stopTimesteps--;

		while (!Ready.isEmpty())
		{
			Process*temp=nullptr;
			Ready.peek(temp);
			if (temp)
			{
				if (!temp->getIschild())
				{
					SchPtr->ToReady(Ready);
				}
				else
				{
					Ready.dequeue(temp);
					SchPtr->ToReadyForking(temp);
				}
			}
			
		}
		if (running)
		{
			running->setStatus(RDY);
			if (!running->getIschild())
			{
				SchPtr->ToReady(running);

			}
			else
			{
				SchPtr->ToReadyForking(running);
			}
		}
		running = nullptr;
		this->expectedFinishTime = 0;
		return true;
	}
	else {

		return false;

	}

}


FCFS_Processor::~FCFS_Processor() {

}
