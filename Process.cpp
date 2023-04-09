#include "Process.h"
#include <fstream>
using namespace std;

Process::Process() {}

Process::Process(int p, int a, int c, int n) {
	PID = p;
	AT = a;
	CT = c;
	N = n;
	RT = -1; //ToDo: check if it was not set before set it else leave it
	Pstatus = NEW;
	RunT = 0;
	CurrentReq = nullptr;
}
void Process::setPID(int id) {
	PID = id;
}

void Process::setTT(int t) {
	TT = t;
	TRT = TT - AT;
	WT = TRT - CT;
}
void Process::setRT(int n) {
	if (RT == -1)
	{
		RT = n-AT;
	}
}

void Process::AddRequest(int IO_R, int IO_D) //TODO:
{
	IO_Request* tempReq = new IO_Request;
	tempReq->IO_D = IO_D;
	tempReq->IO_R = IO_R;
	IO_Ds += IO_D;
	ReqQueue.enqueue(tempReq); //THIS IS SENT BY VALUE!! MAY BE NEEDED TO CHANGE
}

int Process::getAT()
{
	return AT;
}


void Process::IncrementRunT()
{
	Pstatus = RUN;
	RunT++;
	if (CT <= RunT)
	{
		Pstatus = TRM;
		return;
	}
	IO_Request* temp=nullptr;
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


int Process ::getRemtime() {
	if(!ReqQueue.isEmpty())
	{
		IO_Request* temp=nullptr;
		ReqQueue.peek(temp);
		return temp->IO_R - RunT;
	}
	else
	{
		return CT - RunT;
	}
	
}

void Process::PrintInfo(ofstream &file)
{
	file << TT<<"\t"<< PID<< "\t" << AT << "\t" << CT << "\t" << IO_Ds<< "\t" << WT << "\t" << RT << "\t" << TRT << endl;
}

void Process::setStatus(Status s) {

	Pstatus = s;

}



