#include "EDF_Processor.h"
#include "ProcessSch.h"

EDF_Processor::EDF_Processor(ProcessSch* SchedulerPointer) :Processor(SchedulerPointer)
{

}

void EDF_Processor::stateUpdate() {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
		IdealT++;
	}
	else {
		currentState = BUSY;
		BusyT++;
	}

}

void EDF_Processor::printMyReady() {

	std::cout << "processor " << getID() << "[EDF ]: " << Ready.getCount() << " RDY: ";
	Ready.print();

}

void EDF_Processor::AddProcess(Process* NewPrcs)
{
	NewPrcs->setStatus(RDY);
	Ready.enqueue(NewPrcs, NewPrcs->getED());
	expectedFinishTime += NewPrcs->getRemtime();
	stateUpdate();
}


Process* EDF_Processor::RemoveProcess() {

	Process* p = nullptr;
	Ready.dequeue(p);
	if (p)
		expectedFinishTime -= p->getRemtime();
	stateUpdate();
	return p;

}

void EDF_Processor::ScheduleAlgo(int time)
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

EDF_Processor::~EDF_Processor() {

}
