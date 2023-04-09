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

void SJF_Processor::ScheduleAlgo(int time)
{

	if (currentState == IDLE) {
		return;
	}

	if (running == nullptr) {

		Ready.dequeue(running);
		running->setStatus(RUN);
	}
	if (time >= 50 && time <= 60)
	{
		Terminated = running;
		running = nullptr;
		Terminated->setStatus(TRM);
	}
	else if (time >= 1 && time <= 15)
	{
		Blocked = running;
		running = nullptr;
		Blocked->setStatus(BLK);
	}
	else if (time >= 20 && time <= 30) {
		Ready.enqueue(running, running->getRemtime());
		running->setStatus(RDY);
		running = nullptr;

	}


	stateUpdate();

}

SJF_Processor::~SJF_Processor(){

}