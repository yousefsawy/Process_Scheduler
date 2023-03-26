#pragma once
#include "LinkedQueue.h"
#include"DEFS.h"

class Process {
private:
	int PID; //Process ID
	int PT; //Processed time
	int AT; //Arrival time
	int CT; //CPU time
	int N; //number of IO requests
	int TT; //Termination time
	int RT; //Response time
	int TRT; //Turnaround time
	int WT; //Waiting time
	int RunT; //Running time (inside CPU)
	Status Pstatus; //processor status
	LinkedQueue<IO_Request*> ReqQueue; //Queue with the requests !!!ADD PRIQUEUE IF NOT SORTED
	IO_Request* CurrentReq; //Current IO_Request
public:
	Process(){}

	Process(int p, int a, int c, int n) {
		PID = p;
		AT = a;
		CT = c;
		N = n;
		PT = 0;
		RT = -1; //ToDo: check if it was not set before set it else leave it
		Pstatus = NEW;
		RunT = 0;
		CurrentReq = nullptr;
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
		IO_Request* tempReq = new IO_Request;
		tempReq->IO_D = IO_D;
		tempReq->IO_R = IO_R;
		ReqQueue.enqueue(tempReq); //THIS IS SENT BY VALUE!! MAY BE NEEDED TO CHANGE
	}

	int getAT()
	{
		return AT;
	}

	void IncrementRunT(); //Increments the running time inside CPU
	bool isTerminated(); //Checks if process is terminated or not
	bool isIORequest(); //Checks if there is an IORequest
	void IncrementIO_D(); //Increments the IO Duration


};