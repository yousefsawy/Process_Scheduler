#pragma once

#include "LinkedQueue.h"
#include"DEFS.h"

#include <fstream>

using namespace std;

class Process {

	friend ostream& operator<<(ostream&, const Process&);
	friend ostream& operator<<(ostream&, Process*);

private:

	static int count;
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
	int Deadline; //Earliest deadline
	bool MigrateRTF,MigrateMaxW;
	Status Pstatus; //processor status
	LinkedQueue<IO_Request*> ReqQueue; //Queue with the requests !!!ADD PRIQUEUE IF NOT SORTED
	IO_Request* CurrentReq; //Current IO_Request
	//Forking
	bool forked;
	Process* Lchild;
	Process* Rchild;
	bool ischild;

public:

	//Constructors
	Process();
	Process(int a, int c, int ED,int n,bool IC=false);
	//Setters
	void setPID(int id);
	void setTT(int t);
	void Forked();

	void setMigrateRTF();
	void setMigrateMaxW();
	void setRT(int n);
	void AddRequest(int IO_R, int IO_D);
	void setStatus(Status); //Set process status
	void setLchild(Process*);
	void setRchild(Process*);
	//getters
	int getPID() const;
	int getED() const;
	int getTT() const;
	int getAT() const;
	int getWT() const;
	int getRT() const;
	int getTRT() const;
	bool getforked() const;
	bool getMigrateRTF() const;
	bool getMigrateMaxW() const;
	Process* getLchild() const;
	Process* getRchild() const;
	bool getIschild() const;
	static int getCount();
	int getRemtime() const;
	int getRemT() const;
	int getRunT() const;
	//Functions
	void IncrementRunT(); //Increments the running time inside CPU
	bool isTerminated(); //Checks if process is terminated or not
	bool isIORequest(); //Checks if there is an IORequest
	void IncrementIO_D(); //Increments the IO Duration
	void PrintInfo(ofstream &file); //Prints the data of the process
	//Destructor
	~Process();

};