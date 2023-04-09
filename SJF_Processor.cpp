#include"SJF_Processor.h"

SJF_Processor::SJF_Processor() {

}

void SJF_Processor::stateUpdate() {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
	}
	else {
		currentState = BUSY;
	}

}

void SJF_Processor::AddProcess(Process* NewPrcs)
{
	NewPrcs->setStatus(RDY);
	Ready.enqueue(NewPrcs,NewPrcs->getRemtime());
	expectedFinishTime += NewPrcs->getRemtime();
	stateUpdate();
}

void SJF_Processor::ScheduleAlgo()
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

SJF_Processor::~SJF_Processor(){

}