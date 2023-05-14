#include"Processor.h"
#include <cstdlib>
#include <ctime>

int Processor::counter = 0;

Processor::Processor(ProcessSch* SchedulerPointer, int MaxW, int RTF){

	currentState = IDLE;
	expectedFinishTime = 0;
	running = nullptr;
	Terminated = nullptr;
	Blocked = nullptr;
	ID = ++counter;
	SchPtr = SchedulerPointer;
	BusyT = 0;
	IdealT = 0;
	this->MaxW = MaxW;
	this->RTF = RTF;
	stopTimesteps = 0;
	srand(time(NULL));
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

int Processor::pUtil() const
{
	return (BusyT * 100) / (BusyT + IdealT);
}

int Processor::getBusy() const
{
	return BusyT;
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

bool Processor::Migrate(int time)
{
	return false;
}

int Processor::getID() const {

	return ID;

}

void Processor::setSchPtr(ProcessSch* SchedulerPointer)
{
	SchPtr = SchedulerPointer;
}

bool Processor::isOverHeated() {

	return currentState == STOP;

}
