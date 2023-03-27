#include "Process.h"

void Process::IncrementRunT()
{
	Pstatus = RUN;
	RunT++;
	if (CT <= RunT)
	{
		Pstatus = TRM;
		return;
	}
	IO_Request* temp;
	ReqQueue.peek(temp);

	if (!temp)
		return;

	if (temp->IO_R <= RunT)
	{
		CurrentReq = temp;
		ReqQueue.dequeue(temp);
		Pstatus = BLK;
	}
}

bool Process::isTerminated()
{
	if (Pstatus == TRM)
		return true;
	return false;
}

bool Process::isIORequest()
{
	if (Pstatus == BLK)
		return true;
	return false;
}

void Process::IncrementIO_D()
{
	if (CurrentReq)
	{
		CurrentReq->IO_D--;
		if (CurrentReq->IO_D <= 0)
		{
			delete CurrentReq;
			CurrentReq = nullptr;
			Pstatus = RDY;
		}
	}
}



