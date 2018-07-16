#ifndef __DECLARES_H__
#define __DECLARES_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define PIPELINE_SIZE 10

#define RUNNING 0
#define READY 1
#define WAITING 2
#define TERMINATED 3 

#define NONEED 0
#define S1 1
#define S2 2

typedef int Product;
typedef struct PCB {
	char proc_name[20];
	int status;
    int need; //s1 or s2
	int breakpoint;
	struct PCB* next;
} PCB;
typedef struct Semaphore {
	int value;
	PCB *pending;
} Semaphore;

extern Semaphore* s1; //empty
extern Semaphore* s2; //occupied
extern int PC;
extern int product_num;
extern int to_produce;
extern int to_consume;
extern int product_id;
extern int in;
extern int out;
extern Product C;
extern Product X;
extern Product products[PIPELINE_SIZE];
extern PCB* running_proc;
extern PCB* producer;
extern PCB* consumer;

int setRunningProc(PCB* );
int init();
int schedule();
int execute();
int p(Semaphore* );
int v(Semaphore* );
int produce();
int consume();
int put();
int get();

#endif

