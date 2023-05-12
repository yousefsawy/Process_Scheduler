#include "EDF_Processor.h"
#include "ProcessSch.h"

EDF_Processor::EDF_Processor(ProcessSch* SchedulerPointer, int MaxW, int RTF) :Processor(SchedulerPointer, MaxW, RTF)
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
	if (running)
	{
		if (NewPrcs->getED() >= running->getED())
		{
			NewPrcs->setStatus(RDY);
			Ready.enqueue(NewPrcs, NewPrcs->getED());
			expectedFinishTime += NewPrcs->getRemtime();
		}
		else
		{
			Ready.enqueue(running, running->getED());
			running->setStatus(RDY);
			running = NewPrcs;
			running->setStatus(RUN);
			expectedFinishTime += running->getRemtime();
		}
	}
	else
	{
		NewPrcs->setStatus(RDY);
		Ready.enqueue(NewPrcs, NewPrcs->getED());
		expectedFinishTime += NewPrcs->getRemtime();
	}
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

	if (OverHeated) {
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

bool EDF_Processor::OverHeated() {

	if (currentState == STOP) {

		stopTimesteps--;

		if (stopTimesteps == 0) {
			currentState = IDLE;
		}

		return true;

	}

	bool toSTOPState = rand() % 100 <= 5;

	if (toSTOPState) {

		currentState == STOP;
		stopTimesteps = SchPtr->getn();
		stopTimesteps--;

		for (int i = 0; i < Ready.getCount(); i++) {
			SchPtr->ToReady(Ready);
		}
		running->setStatus(RDY);
		SchPtr->ToReady(running);

	}
	else {

		return false;

	}

}