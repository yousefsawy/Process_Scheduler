#pragma once
#include "DEFS.h"
#include <iostream>
#include "ProcessSch.h"
#include <Windows.h>

class UI_Class
{
private:
	UI_Mode Mode;
	ProgramState State; //True if program is finished
	int TimeStep; 
	ProcessSch* PtrSchd;
public:
	UI_Class(UI_Mode Mode);
	void ExecuteUI();
	void Interactive_StepMode();
	void SilentMode();
};

