#include "FCFS_Processor.h"
#include "ProcessSch.h"

FCFS_Processor::FCFS_Processor(ProcessSch* SchedulerPointer) :Processor(SchedulerPointer)
{
}

void FCFS_Processor::stateUpdate() {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
		IdealT++;
	}
	else {
		currentState = BUSY;
		BusyT++;
	}

}

void FCFS_Processor::printMyReady() {

	std::cout << "processor " << getID() << "[FCFS]: " << Ready.getCount() << " RDY: ";
	Ready.print();

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

void FCFS_Processor::AddProcess(Process* NewPrcs)
{
	NewPrcs->setStatus(RDY);
	Ready.enqueue(NewPrcs);
	expectedFinishTime += NewPrcs->getRemtime();
	stateUpdate();
}

Process* FCFS_Processor::RemoveProcess() {
	Process* p = nullptr;
	Ready.dequeue(p);
	if (p)
		expectedFinishTime -= p->getRemtime();
	stateUpdate();
	return p;

}

void FCFS_Processor::ScheduleAlgo(int time)
{

	if (currentState == IDLE) {
		IdealT++;
		return;
	}
	if (running == nullptr) {

		Ready.dequeue(running);
		running->setStatus(RUN);

	}

	running->setRT(time /*timestep*/);
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

	stateUpdate();

}

FCFS_Processor::~FCFS_Processor() {

}
