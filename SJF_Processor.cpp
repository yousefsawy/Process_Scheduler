#include "SJF_Processor.h"
#include "ProcessSch.h"

SJF_Processor::SJF_Processor(ProcessSch* SchedulerPointer) :Processor(SchedulerPointer) 
{

}

void SJF_Processor::stateUpdate() {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
	}
	else {
		currentState = BUSY;
	}

}

void SJF_Processor::printMyReady() {

	std::cout << "processor " << getID() << "[SJF ]: " << Ready.getCount() << " RDY: ";
	Ready.print();

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
	running->setRT(time /*timestep*/);
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

SJF_Processor::~SJF_Processor() {

}