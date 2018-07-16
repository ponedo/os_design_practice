#include "declares.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int disk_init(Disk_block* disk)
{
	int i, j , group_num=(M-1)/N+((M-1)/N==0?0:1);
	Disk_block *p = disk+1;
	
	disk->data[0] = (M<N)? M : N; //super_block
	
	for (i=1; i<disk->data[0]+1; i++)
		disk->data[i] = i;

	for (i=1; i<group_num+1; i++)
	{
		if (i<group_num-1)
		{
			p->data[0] = N;
			for (j=1; j<N+1; j++)
			    p->data[j] = N*i + j;
		}
		else if (i==group_num-1)
		{
			p->data[0] = N - M%N; // descripting the last group
			for (j=1; j<(M-1)%N+2; j++) //1-16 ! not {1-15, 0}
				p->data[j] = N*i + j;
		}
		else if (i==group_num)
			p->data[0] = 0;
		p += N;
	}
	return 1;
}

int writeMA(MA* ma, Disk_block* super_block)
{
	int i;
	for (i=0; i<super_block->data[0]+1; i++)
	    ma->data[i] = super_block->data[i];
	return 1;
}

int writeSB(Disk_block* super_block, MA* ma)
{
	int i;
	for (i=0; i<ma->data[0]+1; i++)
	    super_block->data[i] = ma->data[i];
	return 1;
}

int* allocateDisk(Disk_block* disk, MA* ma, int size)
{
	int k=0;
	int* rtr = (int* )malloc(size*sizeof(int));
	while (true)
	{
		if (ma->data[0]>1)
		{
			int block_num;
			block_num = ma->data[ma->data[0]];
		    (disk+block_num)->occupied = 1;
		    rtr[k++] = block_num;
		    ma->data[0]--;
		}
		else if (ma->data[0]==1)
		{
			int i;
			int new_sb_offset = ma->data[1]; //new super block
			Disk_block* new_sb = disk + new_sb_offset;
			for (i=0; i<N+1; i++)
			    disk->data[i] = new_sb->data[i];//set super_block
			new_sb->occupied = 1;
			rtr[k++] = new_sb_offset;
			ma->data[0]--;
			writeMA(ma, disk);
		}
		if (k>=size) break;
	}
	return rtr;
}

int releaseDisk(Disk_block* disk, MA* ma, int block_num)
{
	Disk_block* target = disk + block_num;
	if (target->occupied==0)
	    return 0;
	else
	{
		if(ma->data[0]<N)
		{
		    target->occupied = 0;
			ma->data[0]++;
			ma->data[ma->data[0]] = block_num;
		}
		else
		{
			int i;
			target->occupied = 0;
			 //create a new group with target itself being the first block
			for (i=0; i<N+1; i++)//ma into the target
				target->data[i] = ma->data[i];
			ma->data[0] = 1;
			ma->data[1] = block_num;
			writeSB(disk, ma);
		}
		return 1;
	}
}

int printGroups(MA* ma, Disk_block* disk)
{
	int i, gid=0, num;
	Disk_block* p=ma;
	while (true)
	{
	    num=p->data[0];
		if (num==0) break;
		
		printf("Group%d: ", gid++);
		for (i=1; i<num+1; i++)
		    printf("%5d",p->data[i]);
		printf("\n");
		
		p = disk + p->data[1];
	}
	printf("\n");
	return 1;
}
