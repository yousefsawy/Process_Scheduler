#include "Process.h"

void Process::IncrementRunT()
{
	RunT++;
	IO_Request* temp;
	ReqQueue.peek(temp);
	if (temp->IO_R == RunT)
	{
		CurrentReq = temp;
		ReqQueue.dequeue(temp);
	}
}

bool Process::isTerminated()
{
	if (CT == RunT)
		return true;
	return false;
}

bool Process::isIORequest()
{
	if (CurrentReq)
		return true;
	return false;
}

void Process::IncrementIO_D()
{
	if (CurrentReq)
	{
		CurrentReq->IO_D--;
		if (CurrentReq->IO_D == 0)
		{
			delete CurrentReq;
			CurrentReq = nullptr;
		}
	}
}



