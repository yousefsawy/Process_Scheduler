#include <fstream> //Needed for the Input/Output function
using namespace std;

#include "Process.h"

int main(void)
{

}

bool InputF(void)
{
	string s = "test"; //File name
	ifstream InputFile(s + ".txt");

	if (!InputFile.is_open())
		return false;

	int FCFS, SJF, RR; //Number of Processors of each type (FCFS, SJF, RR)

	int TS_RR; //Time slice for RR

	int RTF, MAXW; //Process Migration related

	int NumOfProcess; //Number of process

	InputFile >> FCFS >> SJF >> RR >> TS_RR >> RTF >> MAXW >> NumOfProcess;
	
	//TODO: Declare Processors

	for (int i = 0; i < NumOfProcess; i++)
	{
		int AT, PID, CT, N; // Arrival Time, Process ID, CPU Time, Number of process requests  I/O
		InputFile >> AT >> PID >> CT >> N;

		//TODO: Create a Process (PriNode or Node then add it to the processor)
		Process* tempProcess = new Process(PID, AT, CT, N);
		//

		for (int j = 0; j < N; j++)
		{
			int IO_R, IO_D; // I/O Request time, I/O Duration time
			InputFile.ignore();
			InputFile >> IO_R;
			InputFile.ignore();
			InputFile >> IO_D;
			InputFile.ignore();

			//TODO: Add I/O Request to Process
			tempProcess->AddRequest(IO_R, IO_D);

			if (j != N - 1)
				InputFile.ignore();
		}
		return true;
	}
