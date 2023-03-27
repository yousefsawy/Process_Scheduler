#include"Processor.h"

Processor::Processor() {

	currentState = IDLE;
	expectedFinishTime = 0;
	running = nullptr;
	Terminated = nullptr;
	Blocked = nullptr;

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