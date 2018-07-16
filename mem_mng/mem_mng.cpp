#include <stdio.h>
#include <stdlib.h>
#include "declares.h"

int printPageTable(PageEntry* pagetable, int size)
{
	int i;
	printf("\t+=============================+\n");
	for (i=0; i<size; i++)
	{
		printf("\t| Page %4d   in   Block %4d |\n", pagetable->page_num, pagetable->block_num);
		pagetable++;
	}
	printf("\t+=============================+\n");
	return 1;
}

PageEntry* setPageEntry(PageEntry* pos, int page_num, int block_num)
{
	pos->page_num = page_num;
	pos->block_num = block_num;
}

int printBitmap(Bitmap* bitmap)
{
	int i, j , n=MEM_SIZE/8 + (MEM_SIZE%8==0 ? 0 : 1);
	char string[9];
	char temp, mask;
	printf("Bitmap is as follow:\n");
	printf("\t+==========+\n");
	for (i=0; i<n; i++)
	{
		mask = 1;
		temp = bitmap->data[i];
		for (j=0; j<8; j++)
		{
			if ((int)(temp & mask) == 0) string[j] = '0';
			else string[j] = '1';
			mask = mask << 1;
		}
		string[8] = '\0';
		printf("\t| %s |\n", string);
	}
    printf("\t+==========+\n");
    return 1;
}

int setBitmap0(Bitmap* bitmap, int block_id)
{
	int index = block_id/8;
	int offset = block_id%8;
	char temp = bitmap->data[index];
	temp = (temp & ~(1<<offset));
	bitmap->data[index] = temp;
	return 1;
}

int* setBitmap1(Bitmap* bitmap, int size)
{
	/*set lowest available bit to 1*/
	int i, j, k=0, n=MEM_SIZE/8 + (MEM_SIZE%8==0 ? 0 : 1);
	int *rtr = (int* )malloc(size*sizeof(int));
	char mask;
	char temp;
	
	for (i=0; i<n; i++)
	{
		mask = 1;
		temp = bitmap->data[i];
		for (j=0; j<8; j++)
		{
			if ((int)(temp & mask) == 0) // when bit == 0
			{
				temp = temp | mask; // set the bit to 1
				rtr[k++] = 8*i + j;
				if (k>=size) break;
			}
			mask = mask << 1; 
		}
		bitmap->data[i] = temp;
		if (k>=size) break;
	}
	return rtr; // block_num array
}
