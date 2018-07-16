#ifndef __DECLARES_H__
#define __DECLARES_H__

#define N 16
  //group_size
#define M 256
  //block_num
#define BLK_SIZE 63
  //block_size

typedef struct Disk_block
{
	int occupied;
	int data[BLK_SIZE];
} Disk_block;

typedef Disk_block MA;

int disk_init(Disk_block*);
int writeMA(MA*, Disk_block*);
int writeSB(Disk_block*, MA*);
int* allocateDisk(Disk_block*, MA*, int);
int releaseDisk(Disk_block*, MA*, int);
int printGroups(MA*, Disk_block*);

#endif
