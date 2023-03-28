#pragma once
#include "LinkedQueue.h"
#include"DEFS.h"
#include <fstream>
using namespace std;

class Process {
private:
	int PID; //Process ID
	int AT; //Arrival time
	int CT; //CPU time
	int N; //number of IO requests
	int TT; //Termination time
	int RT; //Response time
	int TRT; //Turnaround time
	int WT; //Waiting time
	int RunT; //Running time (inside CPU)
	int IO_Ds; //Total duration of IO_Ds
	Status Pstatus; //processor status
	LinkedQueue<IO_Request*> ReqQueue; //Queue with the requests !!!ADD PRIQUEUE IF NOT SORTED
	IO_Request* CurrentReq; //Current IO_Request
public:
	//Constructors
	Process();
	Process(int p, int a, int c, int n);
	//Setters
	void setPID(int id);
	void setTT(int t); 
	void setRT(int n);
	void AddRequest(int IO_R, int IO_D);
	int getAT();
	//Functions
	void IncrementRunT(); //Increments the running time inside CPU
	bool isTerminated(); //Checks if process is terminated or not
	bool isIORequest(); //Checks if there is an IORequest
	void IncrementIO_D(); //Increments the IO Duration
	int getRemtime();
	void PrintInfo(ofstream &file); //Prints the data of the process


};