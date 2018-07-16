#ifndef __DECLARES_H__
#define __DECLARES_H__

#define MEM_SIZE 64

typedef struct PageEntry
{
	int page_num;
	int block_num;
} PageEntry;

typedef struct PCB
{
	unsigned pid;
	unsigned mem_size;
	PageEntry* pagetable;
	struct PCB* next;
} PCB;

typedef struct BLOCK
{
	int block_id;
} BLOCK;

typedef struct Bitmap
{
	char data[MEM_SIZE/8 + (MEM_SIZE%8==0 ? 0 : 1)];
} Bitmap;

int printPageTable(PageEntry*, int);
PageEntry* setPageEntry(PageEntry*, int, int);
int printBitmap(Bitmap*);
int setBitmap0(Bitmap*, int);
int* setBitmap1(Bitmap*, int);

#endif
