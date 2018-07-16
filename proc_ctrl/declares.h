#ifndef __DECLARES_H__
#define __DECLARES_H__

typedef struct PCB {
	unsigned pid;
	struct PCB *next;
	unsigned remain_time;
	unsigned priority;
	int status;
} PCB;

PCB * createProc(unsigned, unsigned, unsigned);
int insertProc(PCB *, PCB *);
int runProc(PCB *, PCB *);

#endif
