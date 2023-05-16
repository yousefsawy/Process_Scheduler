#include"RR_Processor.h"
#include "ProcessSch.h"

RR_Processor::RR_Processor(ProcessSch* SchedulerPointer,int TS, int MaxW, int RTF) :Processor(SchedulerPointer, MaxW, RTF),timeSlice(TS)
{
	currentTimeSlice = 0;
}



void RR_Processor::stateUpdate(bool t = true) {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
		if(t)
			IdealT++;
	}
	else {
		currentState = BUSY;
		if(t)
			BusyT++;
	}

}

void RR_Processor::printMyReady() {

	std::cout << "processor " << getID() << "[RR  ]: " << Ready.getCount() << " RDY: ";
	if (isOverHeated())
	{
		std::cout << "OVERHEATED!!!";
	}
	else
	{
		Ready.print();
	}

}

bool RR_Processor::Migrate(int)
{
	bool Migrated = false;
	int time = running->getRemtime();
	if (time<RTF)
	{
		Migrated = SchPtr->MigrateToSJF(running);
		if (Migrated)
		{
			expectedFinishTime -= running->getRemtime();
			running = nullptr;
			stateUpdate(false);
		}
	}
	return Migrated;
}

void RR_Processor::AddProcess(Process* p) {

	p->setStatus(RDY);
	Ready.enqueue(p);
	expectedFinishTime += p->getRemtime();
	stateUpdate();

}

Process* RR_Processor::RemoveProcess() {

	Process* p = nullptr;
	Ready.dequeue(p);
	if (p)
		expectedFinishTime -= p->getRemtime();
	stateUpdate();
	return p;

}

void RR_Processor::ScheduleAlgo(int time) {

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
		currentTimeSlice = 0;

	}
	running->setRT(time /*timestep*/);
	running->IncrementRunT();
	expectedFinishTime--;
	currentTimeSlice++;

	bool Mig = Migrate(time);
	if (Mig)
	{
		while (Mig)
		{
			if (currentState == IDLE)
				return;
			Ready.dequeue(running);
			Mig = Migrate(time);
		}
		return;
	}

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
	else if (currentTimeSlice == timeSlice) {

		Process* temp = running;
		running = nullptr;
		Ready.enqueue(temp);

	}

	stateUpdate();

}


RR_Processor::~RR_Processor() {

}

bool RR_Processor::OverHeated() {

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
		stopTimesteps--;

		while (!Ready.isEmpty()) {
			SchPtr->ToReady(Ready);
		}
		if (running)
		{
			running->setStatus(RDY);
			SchPtr->ToReady(running);
		}
		running = nullptr;
		this->expectedFinishTime = 0;
		return true;
	}
	else {

		return false;

	}

}