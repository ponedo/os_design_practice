#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declares.h"

int main()
{
	int remain=M, exit=0;
	char command[20];
	Disk_block* disk = (Disk_block* )malloc(M*sizeof(Disk_block));//Disk_block disk[M]
	MA* ma = (MA* )malloc(sizeof(MA)); //memory access
	
	disk_init(disk);
	writeMA(ma, disk);
	remain--;
	
	printf("Welcome to disk management simulation!\n");
	
	do
	{
		printf("Check the status of the groups(check), \
allocate(allocate), release(release) or exit(exit)?\n");
        
        do
        {
        	printf(">> ");
        	scanf("%s", &command);
        	
			if (strcmp(command, "check")==0)
			{
				printGroups(ma, disk);
				break;
			}
			else if (strcmp(command, "allocate")==0)
			{
				int i, size;
				int* blocks;
				printf("Please input the to-allocate size(How many blocks?): ");
        	    scanf("%d", &size);
				blocks = allocateDisk(disk, ma, size);
				printf("The following blocks have been allocated:\n");
				for (i=0; i<size; i++)
				    printf("%5d", blocks[i]);
				printf("\n");
				free(blocks);
				break;
			}
			else if (strcmp(command, "release")==0)
			{
				int block_id;
				printf("Please input the to-release block id: ");
        	    scanf("%d", &block_id);
        	    if (block_id>M-1) printf("Illegal block address! Please input again!\n");
        	    if (releaseDisk(disk, ma, block_id)) printf("Release succeeded!\n");
        	    else printf("Release failed!\nThe block No. %d is already empty. No release opertion on it can be performed!\n");
        	    break;
			}
			else if (strcmp(command, "exit")==0)
			{
				exit = 1;
				break;
			}
			else
			{
				printf("Invalid command! Please input again!");
			}
			
		} while (true);
        
	}while (!exit);
	getchar();
}
