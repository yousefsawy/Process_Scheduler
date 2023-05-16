#ifndef UI_CLASS_H
#define UI_CLASS_H

#include "DEFS.h"
#include <iostream>
#include <Windows.h>

class ProcessSch;

class UI_Class
{
private:
	UI_Mode Mode;
	ProgramState State; //True if program is finished
	int TimeStep;
	ProcessSch* PtrSchd;
public:
	UI_Class(ProcessSch*);
	void ExecuteUI();
	void Interactive_StepMode();
	void SilentMode();
};

#endif