#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declares.h"

int main()
{
	int i;
	int exit=0;
	unsigned max_pid=0;
	int block_remain = MEM_SIZE;
	char command[20];
	PCB* PCB_head = (PCB* )malloc(sizeof(PCB));
	Bitmap* bitmap = (Bitmap* )malloc(sizeof(Bitmap));
	PCB_head->next=NULL;
	for (i=0; i<MEM_SIZE/8 + (MEM_SIZE%8==0 ? 0 : 1); i++)
	{
		bitmap->data[i]='\0';
	}
	
	printf("Welcome to memory management simulation!\n");
	do
	{
		printf("Current memory condition: %d blocks remaining.", block_remain);
		printBitmap(bitmap);
		printf("Check pagetable(check), create a new process(add), \
release the memory occupied by a process(release) or exit(exit)?\n");

        do
        {
        	printf(">> ");
		    scanf("%s", &command);
		    if (strcmp(command, "exit")==0)
			{
				exit = 1;
				break;
			}
		    else if(strcmp(command, "check")==0)
		    {
		    	int found=0; unsigned pid; PCB* p=PCB_head->next;
		    	printf("Please input the to-check pid: ");
		    	scanf("%u", &pid);
		    	while(p!=NULL)
		    	{
		    		if (p->pid==pid)
					{
						printPageTable(p->pagetable, p->mem_size);
						found = 1;
						break;
					}
					p = p->next;
				}
				if(!found) printf("Invalid pid!\n");
				break;
		    }
		    else if(strcmp(command, "add")==0)
		    {
		    	int mem_size;
		    	printf("Please input the to-occupy \
memory blocks of the new process: ");
                scanf("%d", &mem_size);
                if (mem_size > block_remain)
				    printf("No enough memory blocks!\n");
                else
                {
                	PCB* new_proc = (PCB* )malloc(sizeof(PCB));
                	new_proc->pid = max_pid;
                	new_proc->mem_size = mem_size;
                	new_proc->next = PCB_head->next;
                	PCB_head->next = new_proc;
                	
                	int* blocks;
                	PageEntry* pagetable = (PageEntry* )malloc(mem_size*sizeof(PageEntry));
					new_proc->pagetable = pagetable;
                	blocks = setBitmap1(bitmap, mem_size); // set bitmap
                	
                	for (i=0; i<mem_size; i++) //set pagetable
                		setPageEntry(pagetable++, i, blocks[i]);
                	free(blocks);
					block_remain -= mem_size; // decrease available block number
                	
                	printf("Process %d created, pagetable is as follow: \n", max_pid++);
                	printPageTable(new_proc->pagetable, mem_size);
				}
		    	break;
		    }
		    else if(strcmp(command, "release")==0)
		    {
		    	unsigned pid;
		    	PCB* p=PCB_head->next;
		    	PageEntry* pagetable;
		    	
		    	printf("Please input the to-release process pid: ");
		    	scanf("%u", &pid);
		    	
		    	while(p!=NULL)
		    	{
		    		if (p->pid==pid) break; // find the PCB
					p = p->next;
				}
				if (p==NULL) printf("Invalid pid! Please input a correct pid.\n");
				else
				{
				    int i, size;
					size = p->mem_size;
				    pagetable = p->pagetable;
				    for (i=0; i<size; i++)
					    setBitmap0(bitmap, pagetable++->block_num);  
		    	    free(p->pagetable);
				    PCB_head->next = p->next;
				    free(p);
				    block_remain += size;
				}
				break;
		    }
		    else printf("Invalid command! Please input once again!\n");
		} while(true); //give a command
        
	
	} while(!exit);
	getchar();
	
}
