#include "SJF_Processor.h"
#include "ProcessSch.h"

SJF_Processor::SJF_Processor(ProcessSch* SchedulerPointer, int MaxW, int RTF) :Processor(SchedulerPointer, MaxW, RTF) 
{

}

void SJF_Processor::stateUpdate(bool t = true) {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
		IdealT++;
	}
	else {
		currentState = BUSY;
		BusyT++;
	}

}

void SJF_Processor::printMyReady() {

	std::cout << "processor " << getID() << "[SJF ]: " << Ready.getCount() << " RDY: ";
	if (isOverHeated())
	{
		std::cout << "OVERHEATED!!!";
	}
	else
	{
		Ready.print();
	}

}

void SJF_Processor::AddProcess(Process* NewPrcs)
{
	NewPrcs->setStatus(RDY);
	Ready.enqueue(NewPrcs,NewPrcs->getRemtime());
	expectedFinishTime += NewPrcs->getRemtime();
	stateUpdate();
}


Process* SJF_Processor::RemoveProcess() {

	Process* p = nullptr;
	Ready.dequeue(p);
	if (p)
		expectedFinishTime -= p->getRemtime();
	stateUpdate();
	return p;

}

void SJF_Processor::ScheduleAlgo(int time)
{

	if (currentState == IDLE) {
		IdealT++;
		return;
	}

	if (OverHeated()) {
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

SJF_Processor::~SJF_Processor() {

}

bool SJF_Processor::OverHeated() {

	if (currentState == STOP) {

		stopTimesteps--;

		if (stopTimesteps == 0) {
			currentState = IDLE;
		}

		return true;

	}

	bool toSTOPState = rand() % 1000 <= 5;

	if (toSTOPState) {

		currentState = STOP;
		stopTimesteps = SchPtr->getn();

		while (!Ready.isEmpty()) {

			Process* temp = nullptr;
			Ready.dequeue(temp);
			SchPtr->ToReady(temp);

		}

		if (running)
		{
			running->setStatus(RDY);
			SchPtr->ToReady(running);
			running = nullptr;
		}

		this->expectedFinishTime = 0;
		return true;

	}
	else {

		return false;

	}

}