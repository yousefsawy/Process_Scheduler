#include "FCFS_Processor.h"
#include "ProcessSch.h"

FCFS_Processor::FCFS_Processor()
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

void FCFS_Processor::KillRandom()
{
	Process* temp = nullptr;
	if (count == 0)
		return;
	int index = rand() % count;
	Ready.deleteMid(index, temp);
	if (temp)
	{
		temp->setStatus(TRM);
		SchPtr->AddTerminated(temp);
	}
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

	KillRandom();
	

	stateUpdate();

}
