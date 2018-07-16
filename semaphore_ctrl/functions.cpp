#include "declares.h"

int setRunningProc(PCB* loaded)
{
	loaded->status=RUNNING;
	running_proc = loaded;
}

int init()
{
	in = 0;
	out = 0;
	
	s1->value = 10;
	s1->pending = NULL;
	s2->value = 0;
	s2->pending = NULL;
	PC = 0;
	product_id = 0;
	product_num = 0;
	setRunningProc(producer);
	
	strcpy(producer->proc_name, "producer");
	producer->status = READY;
	producer->need = NONEED;
	producer->breakpoint = 0;
	producer->next = NULL;
	
	strcpy(consumer->proc_name, "consumer");
	consumer->status = READY;
	consumer->need = NONEED;
	consumer->breakpoint = 0;
	consumer->next = NULL;
	
	return 0;
}

int schedule()
{
	while (true)
	{
		Sleep(200);
		running_proc->breakpoint = PC;
		if (!(producer->status==READY || consumer->status==READY)) break;
		if (producer->status==READY && consumer->status==READY)
		{
			srand((unsigned)time(NULL));
		    (rand()%2==0) ? setRunningProc(producer) : setRunningProc(consumer);
		}
		else if (producer->status==WAITING || producer->status==TERMINATED)
		{
			setRunningProc(consumer);
		}
		else if (consumer->status==WAITING || consumer->status==TERMINATED)
		{
			setRunningProc(producer);
		}
		PC = running_proc->breakpoint;
		execute();
	}
	return 0;
}

int execute()
{
	if (running_proc==producer)
	{
		switch(PC) //PA
		{
			case 0: PC++; produce(); running_proc->status=READY; break;
			case 1: PC++; p(s1); break;
			case 2: PC++; put(); running_proc->status=READY; break;
			case 3: PC++; v(s2); to_produce--; break;
			case 4: PC++; PC=0; running_proc->status=READY; break;
		}
	}
	else if (running_proc==consumer)
	{
		switch(PC) //SA
		{
			case 0: PC++; p(s2); break;
			case 1: PC++; get(); running_proc->status=READY; break;
			case 2: PC++; v(s1); break;
			case 3: PC++; consume(); running_proc->status=READY; break;
			case 4: PC++; PC=0; running_proc->status=READY; break;
		}
	}
	if (to_produce<=0)
		producer->status=TERMINATED;
	if (to_consume<=0)
		consumer->status=TERMINATED;
	return 0;
}

int p(Semaphore* s)
{
	s->value--;
	if (s->value<0)
	{
		running_proc->status = WAITING;
		running_proc->need = (s==s1)? S1 : ((s==s2)? S2 : NONEED);
		//insert to tail
		s->pending = running_proc;
	}
	else
	    running_proc->status = READY;
}

int v(Semaphore* s)
{
	s->value++;
	if (s->value<=0)
	{
		s->pending->status = READY;
	}
	running_proc->status = READY;
}

int produce()
{
	C = product_id;
	printf("Producing product No. %d.\n", product_id);
	product_id++;
	return 0;
}

int consume()
{
	to_consume--;
	printf("Product No. %d consumed.\n", X);
	return 0;
}

int put()
{
	products[in] = C;
	in = (in+1)%PIPELINE_SIZE;
	product_num++;
    printf("  A product is put into the pipeline. Currently product number on pipeline: %d\n", product_num);
	return 0;
}

int get()
{
	X = products[out];
	out = (out+1)%PIPELINE_SIZE;
	product_num--;
	printf("  A product is taken from the pipeline. Currently product number on pipeline: %d\n", product_num);
	return 0;
}


