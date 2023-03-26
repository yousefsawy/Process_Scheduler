#pragma once
#include "LinkedQueue.h"
#include"DEFS.h"

class Process {
private:
	int PID;
	int AT;
	int CT;
	int N;
	int TT;
	int RT;
	int TRT;
	int WT;
	Status Pstatus;
	LinkedQueue<IO_Request> ReqQueue; //Queue with the requests !!!ADD PRIQUEUE IF NOT SORTED
public:

	Process(int p, int a, int c, int n) {
		PID = p;
		AT = a;
		CT = c;
		N = n;
		Pstatus = NEW;
	}
	void setPID(int id) {
		PID = id;

	}

	void setTT(int t) {
		TT = t;
		TRT = TT - AT;
		WT = TRT - CT;
	}
	void setRT(int n) {
		RT = AT - n;
	}

	void AddRequest(int IO_R, int IO_D) //TODO:
	{
		IO_Request tempReq; 
		tempReq.IO_D = IO_D;
		tempReq.IO_R = IO_R;
		ReqQueue.enqueue(tempReq); //THIS IS SENT BY VALUE!! MAY BE NEEDED TO CHANGE
	}



};