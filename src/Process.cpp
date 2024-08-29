#include "Process.h"

using namespace std;

int Process::count = 0;
Process::Process() {}

Process::Process(int a, int c,int ED, int n, bool IC) {
	PID = ++count;
	AT = a;
	CT = c;
	N = n;
	Deadline = ED;
	RT = -1;
	Pstatus = NEW;
	RunT = 0;
	CurrentReq = nullptr;
	Lchild = nullptr;
	Rchild = nullptr;
	ischild = IC;
	forked = false;
	MigrateRTF = false;
	MigrateMaxW = false;
}

void Process::setPID(int id) {
	PID = id;
}

int Process::getPID() const
{
	return PID;
}

int Process::getED() const
{
	return Deadline;
}

int Process::getTT() const
{
	return TT;
}

void Process::setTT(int t) {
	TT = t;
	TRT = TT - AT;
	WT = TRT + getRemT() - CT;
}

void Process::Forked()
{
	forked = true;
}

void Process::setMigrateRTF()
{
	MigrateRTF = true;
}

void Process::setMigrateMaxW()
{
	MigrateMaxW = true;
}

void Process::setRT(int n) {
	if (RT == -1)
	{
		RT = n - AT;
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

int Process::getAT() const
{
	return AT;
}
int Process::getWT() const
{
	return WT;
}

int Process::getRT() const
{
	return RT;
}

int Process::getTRT() const
{
	return TRT;
}

bool Process::getforked() const
{
	return forked;
}

bool Process::getMigrateRTF() const
{
	return MigrateRTF;
}

bool Process::getMigrateMaxW() const
{
	return MigrateMaxW;
}

Process* Process::getLchild() const
{
	return Lchild;
}

Process* Process::getRchild() const
{
	return Rchild;
}

bool Process::getIschild() const
{
	return ischild;
}

int Process::getCount()
{
	return count;
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
	IO_Request* temp = nullptr;
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

int Process::getRemT() const
{
	return CT - RunT;

}

int Process::getRunT() const
{
	return RunT;
}

int Process::getRemtime() const {
	if (!ReqQueue.isEmpty())
	{
		IO_Request* temp = nullptr;
		ReqQueue.peek(temp);
		return temp->IO_R - RunT;
	}
	else
	{
		return CT - RunT;

	}
}

	void Process::PrintInfo(ofstream & file)
	{
		file << TT << "\t" << PID << "\t" << AT << "\t" << CT << "\t" << IO_Ds << "\t" << WT << "\t" << RT << "\t" << TRT << endl;
	}



	void Process::setStatus(Status s) {

		Pstatus = s;

	}

	void Process::setLchild(Process * child)
	{
		Lchild = child;
	}

	void Process::setRchild(Process * child)
	{
		Rchild = child;
	}

	Process::~Process() {

	}

	std::ostream& operator<<(std::ostream & output, const Process & p) {

		output << p.PID;
		return output;

	}

	std::ostream& operator<<(std::ostream & output, Process * p) {

		output << p->PID;
		return output;

	}