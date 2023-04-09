#include"RR_Processor.h"

RR_Processor::RR_Processor() {

	currentTimeSlice = 0;

}

void RR_Processor::stateUpdate() {

	if (running == nullptr && Ready.isEmpty()) {
		currentState = IDLE;
	}
	else {
		currentState = BUSY;
	}

}

void RR_Processor::AddProcess(Process* p) {

	p->setStatus(RDY);
	Ready.enqueue(p);
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

	currentTimeSlice++;

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
		Ready.enqueue(running);
		running->setStatus(RDY);
		running = nullptr;

	}
	else if (currentTimeSlice == timeSlice) {

		Process* temp = running;
		running = nullptr;
		Ready.enqueue(temp);

	}

	stateUpdate();

}

void RR_Processor::setTimeSlice(int t)
{
	timeSlice = t;
}

RR_Processor::~RR_Processor() {

}