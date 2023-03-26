#ifndef DEFS_H
#define DEFS_H
// This file contains some definitions to be used in the project

enum Status
{
	NEW,
	RDY,
	RUN,
	BLK,
	TRM
};

struct IO_Request //QUESTION: IS THE REQUEST SORTED?
{
	int IO_R; //Request Time
	int IO_D; //Request Duration
};

//Enum for processor state
enum State
{
	IDLE,
	BUSY
};


#endif