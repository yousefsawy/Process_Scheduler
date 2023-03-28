#include "FCFS_Processor.h"

FCFS_Processor::FCFS_Processor()
{}

void FCFS_Processor::AddProcess(Process* NewPrcs)
{
	Ready.enqueue(NewPrcs);
	expectedFinishTime += NewPrcs->getRemtime();
}

void FCFS_Processor::ScheduleAlgo(int time)
{
	if (!running)
	{
		Ready.dequeue(running);
	}
		
	if (!running)
	{
		currentState = IDLE;
		return;
	}
	running->setRT(time/*timestep*/);
	running->IncrementRunT();
	currentState = BUSY;
	if (running->isTerminated())
	{
		Terminated = running;
		running = nullptr;
		return;
	}

	if (running->isIORequest())
	{
		Blocked = running;
		running = nullptr;
	}

}

