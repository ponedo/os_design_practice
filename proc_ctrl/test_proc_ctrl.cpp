#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "declares.h"

int main()
{
	unsigned proc_num;
	PCB *ready_queue_head;
	PCB *terminated_queue_head;
	PCB *p;
	int i;
	
	ready_queue_head = (PCB *)malloc(sizeof(PCB));
	ready_queue_head->priority = 0-1; //MAX priority
	ready_queue_head->next = NULL; //necessary! avoid bugs!
	
	terminated_queue_head = (PCB *)malloc(sizeof(PCB));
	terminated_queue_head->next = NULL; //necessary! avoid bugs!
	
	printf("Welcome to process control test!\n\
Please input the number of processes: ");
	scanf("%u", &proc_num);
	for (i=0; i<proc_num; i++) //establish link-table
	{
		unsigned time, priority;
		printf("Please input the priority and \
to-run time of the process %d: ", i);
		scanf("%u %u", &priority, &time);
		p = createProc(i, time, priority);
		insertProc(p, ready_queue_head);
	}
	
	while (runProc(ready_queue_head, terminated_queue_head)) ;
	
	printf("Process control ends.\n");
	getchar(); 
	
	return 0;
}
