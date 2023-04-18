#include "UI_Class.h"
#include "ProcessSch.h"


UI_Class::UI_Class(ProcessSch* SchedulerPtr)
{
	int mode;
	std::cout << "Enter 1 for Interactive, 2 for Step, 3 for Silent : ";
	std::cin >> mode;
	std::cin.ignore();
	switch (mode)
	{
	case 1:
		Mode = Interactive;
		break;
	case 2:
		Mode = Step;
		break;
	case 3:
		Mode = Silent;
		break;
	default:
		Mode = Interactive;
	}
	PtrSchd = SchedulerPtr;
	State = Start;
	TimeStep = 0;
}

void UI_Class::ExecuteUI()
{
	TimeStep++;
	if (Mode == Interactive || Mode == Step)
		Interactive_StepMode();
	if (Mode == Silent)
		SilentMode();

}

void UI_Class::Interactive_StepMode()
{
	if (State == Start)
	{
		if (Mode == Step)
			std::cout << "Step-By-Step Mode.......    Simulation starts... \n";

		if (Mode == Interactive)
			std::cout << "Interactive Mode.......    Simulation starts... \n";
		State = Run;
	}

	std::cout << "Current Timestep: " << TimeStep << "\n";

	std::cout << "-------------------- RDY Processes --------------------\n";
	PtrSchd->PrintRDY();

	std::cout << "-------------------- BLK Processes --------------------\n";
	PtrSchd->PrintBLK();

	std::cout << "-------------------- RUN Processes --------------------\n";
	PtrSchd->PrintRun();

	std::cout << "-------------------- TRM Processes --------------------\n";
	PtrSchd->PrintTRM();

	if (Mode == Interactive)
	{
		std::cout << "PRESS ANY KEY TO MOVE TO NEXT STEP!\n";
		getchar();
	}

	if (Mode == Step)
		Sleep(1000);


}


void UI_Class::SilentMode()
{
	if (State == Start)
	{
		std::cout << "Silent Mode.......    Simulation Starts";
		State = Run;
	}

	if (TimeStep % 10000 == 0)
		std::cout << ".";


	if (State == End)
		std::cout << "\nSimulation ends, Output file created";
}
