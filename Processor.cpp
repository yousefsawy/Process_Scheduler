#include"Processor.h"

Processor::Processor() {

	currentState = IDLE;
	expectedFinishTime = 0;
	running = nullptr;

}

bool Processor::isIdle() const{

	return currentState == IDLE;

}

int Processor::getExpectedFinishTime() const {

	return expectedFinishTime;

}

Process* Processor::RequestBlocked() {

	Process* temp = running;
	running = nullptr;
	return temp;

}

Process* Processor::RequestTerminated() {

	Process* temp = running;
	running = nullptr;
	return temp;

}

Processor::~Processor() {

}