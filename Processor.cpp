#include"Processor.h"

int Processor::counter = 0;

Processor::Processor(ProcessSch* SchedulerPointer){

	currentState = IDLE;
	expectedFinishTime = 0;
	running = nullptr;
	Terminated = nullptr;
	Blocked = nullptr;
	ID = ++counter;
	SchPtr = SchedulerPointer;
}

bool Processor::isRunning() const {

	return running != nullptr;

}

void Processor::printRunning() {

	std::cout << *running << "(P" << getID() << ")";

}

bool Processor::isIdle() const{

	return currentState == IDLE;

}

int Processor::getExpectedFinishTime() const {

	return expectedFinishTime;

}

Process* Processor::RequestBlocked() {

	Process* temp = Blocked;
	Blocked = nullptr;
	return temp;

}

Process* Processor::RequestTerminated() {

	Process* temp = Terminated;
	Terminated = nullptr;
	return temp;

}

Processor::~Processor() {

}

int Processor::Find(int)
{
	return -1;
}

Process* Processor::getRun()
{
	return running;
}

int Processor::getID() const {

	return ID;

}

void Processor::setSchPtr(ProcessSch* SchedulerPointer)
{
	SchPtr = SchedulerPointer;
}
