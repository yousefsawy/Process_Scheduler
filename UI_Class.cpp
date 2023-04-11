#include "UI_Class.h"

UI_Class::UI_Class(UI_Mode Mode)
{
	this->Mode = Mode;
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
		State == Run;
	}

	if (TimeStep % 60 == 0)
		std::cout << ".";


	if (State == End)
		std::cout << "\nSimulation ends, Output file created";
}
