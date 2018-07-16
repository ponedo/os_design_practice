/*CPU control with priority*/
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "declares.h"

PCB * createProc(unsigned pid, unsigned remain_time, unsigned priority)
{
	PCB *p;
	p = (PCB *)malloc(sizeof(PCB));
	p->pid = pid;
	p->priority = priority;
	p->remain_time = remain_time; //remain_time > 0
	p->next = NULL;
	p->status = READY;
	return p;	
}

int insertProc(PCB *new_proc, PCB *queue_head)
{
	//insert to right position according to priority(decreasing)
	PCB *p, *pre;
	pre = queue_head;
	p = pre->next;
	while (p!=NULL)
	{
		if (new_proc->priority > p->priority)
		  break;
		pre = p;
		p = p->next;
	}
	new_proc->next = pre->next;
	pre->next = new_proc;
	return 1;
}

int runProc(PCB *ready_queue_head, PCB *terminated_queue_head)
{
	if (ready_queue_head->next==NULL)
	    return 0;
	else
	{
		/*run*/
		PCB *p = ready_queue_head->next;
		ready_queue_head->next = p->next;
		p->next = NULL; //remove p from ready queue
		p->priority = p->priority==0 ? 0 : (p->priority)-1;
		p->remain_time = p->remain_time==0 ? 0 : (p->remain_time)-1;
		printf("Current running process pid: %u, \
priority: %u, remaining time: %u.\n", p->pid, p->priority, p->remain_time);
		
		if (p->remain_time==0)
		{
			p->status = END;
			p->next = terminated_queue_head->next;
			terminated_queue_head->next = p;
			//insert p into terminated_queue
		}
		else
		{
			insertProc(p, ready_queue_head);
		}
		return 1;
	}
}
