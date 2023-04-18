#include "FCFS_Processor.h"
#include "ProcessSch.h"

FCFS_Processor::FCFS_Processor(ProcessSch* SchedulerPointer):Processor(SchedulerPointer)
{
	count = 0;
}

void FCFS_Processor::stateUpdate() {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
	}
	else {
		currentState = BUSY;
	}

}

void FCFS_Processor::printMyReady() {

	std::cout << "processor " << getID() << "[FCFS]: " << Ready.getCount() << " RDY: ";
	Ready.print();

}

bool FCFS_Processor::KillSignal(int PID)
{
	int index = Find(PID);
	if (index == -1)
		return false;

	Process* temp = nullptr;
	Ready.deleteMid(index, temp);
	if (!temp)
		return false;

	SchPtr->AddTerminated(temp);
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
	count++;
}

void FCFS_Processor::ScheduleAlgo(int time)
{

	if (currentState == IDLE) {
		return;
	}
	
	if (running == nullptr) {

		Ready.dequeue(running);
		if (!running)
			return;
		running->setStatus(RUN);
		count--;
	}

	if (time >= 50 && time <= 60)
	{
		running->setStatus(TRM);
		SchPtr->AddTerminated(running);
		running = nullptr;
	}
	else if (time >= 1 && time <= 15)
	{
		running->setStatus(BLK);
		SchPtr->AddBlocked(running);
		running = nullptr;
	}
	else if (time >= 20 && time <= 30) {
		Ready.enqueue(running);
		running->setStatus(RDY);
		running = nullptr;
		count++;
	}	

	stateUpdate();

}

FCFS_Processor::~FCFS_Processor() {

}
