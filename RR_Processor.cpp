#include"RR_Processor.h"
#include "ProcessSch.h"

RR_Processor::RR_Processor(ProcessSch* SchedulerPointer,int TS) :Processor(SchedulerPointer),timeSlice(TS)
{
	currentTimeSlice = 0;
}


/*
RR_Processor::RR_Processor() {

	currentTimeSlice = 0;

}
*/
void RR_Processor::stateUpdate() {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
	}
	else {
		currentState = BUSY;
	}

}

void RR_Processor::printMyReady() {

	std::cout << "processor " << getID() << "[ RR ]: " << Ready.getCount() << " RDY: ";
	Ready.print();

}

void RR_Processor::AddProcess(Process* p) {

	p->setStatus(RDY);
	Ready.enqueue(p);
	expectedFinishTime += p->getRemtime();
	stateUpdate();

}

void RR_Processor::ScheduleAlgo(int time) {

	if (currentState == IDLE) {
		return;
	}

	if (running == nullptr) {

		Ready.dequeue(running);
		running->setStatus(RUN);
		currentTimeSlice = 0;

	}
	running->setRT(time /*timestep*/);
	running->IncrementRunT();
	currentTimeSlice++;

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

/*
void RR_Processor::setTimeSlice(int t)
{
	timeSlice = t;
}
*/

RR_Processor::~RR_Processor() {

}