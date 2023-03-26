#include "FCFS_Processor.h"

FCFS_Processor::FCFS_Processor()
{}

void FCFS_Processor::AddProcess(Process* NewPrcs)
{
	Ready.enqueue(NewPrcs);
}

void FCFS_Processor::ScheduleAlgo()
{
	if (!running)
		Ready.dequeue(running);

	if (!running)
	{
		currentState = IDLE;
		return;
	}

	running->IncrementRunT();

	if (running->isTerminated())
	{
		Terminated = running;
		running = nullptr;
	}

	if (running->isIORequest())
	{
		Blocked = running;
		running = nullptr;
	}

}

