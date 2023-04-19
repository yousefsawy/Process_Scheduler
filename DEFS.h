// This file contains some definitions to be used in the project
#ifndef DEFS_H
#define DEFS_H

//Enum for process status
enum Status
{
	NEW,
	RDY,
	RUN,
	BLK,
	TRM
};

//Enum for processor state
enum State
{
	IDLE,
	BUSY//,STOP
};

struct IO_Request //QUESTION: IS THE REQUEST SORTED?
{
	int IO_R; //Request Time
	int IO_D; //Request Duration
};

enum UI_Mode
{
	Interactive,
	Step,
	Silent
};

enum ProgramState
{
	Start,
	Run,
	End
};

#endif