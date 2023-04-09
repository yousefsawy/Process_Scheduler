#include "FCFS_Processor.h"

FCFS_Processor::FCFS_Processor()
{}

void FCFS_Processor::stateUpdate() {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
	}
	else {
		currentState = BUSY;
	}

}

void FCFS_Processor::AddProcess(Process* NewPrcs)
{
	NewPrcs->setStatus(RDY);
	Ready.enqueue(NewPrcs);
	expectedFinishTime += NewPrcs->getRemtime();
	stateUpdate();
	NewPrcs->setPtrPrcr(this);
}


void FCFS_Processor::ScheduleAlgo()
{

	if (currentState == IDLE) {
		return;
	}

	if (running == nullptr) {

		Ready.dequeue(running);
		running->setStatus(RUN);
	}

	running->IncrementRunT();

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

void FCFS_Processor::TerminateProcess(Process*)
{
	//TODO
}

Process* FCFS_Processor::GetProcess(int PID)
{
	//TODO
	return nullptr;
}
