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
	TRM,
	ORPH
};

//Enum for processor state
enum State
{
	//STOPPED,            ..//Bonus
	IDLE,
	BUSY
};

struct IO_Request //QUESTION: IS THE REQUEST SORTED?
{
	int IO_R; //Request Time
	int IO_D; //Request Duration
};

#endif