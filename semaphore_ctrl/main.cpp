#include <iostream>
#include "declares.h"

Semaphore* s1 = (Semaphore* )malloc(sizeof(Semaphore));
Semaphore* s2 = (Semaphore* )malloc(sizeof(Semaphore));
int PC;
int product_num;
int to_produce;
int to_consume;
int product_id;
int in;
int out;
Product C;
Product X;
Product products[PIPELINE_SIZE];
PCB* running_proc;
PCB* producer = (PCB* )malloc(sizeof(PCB));
PCB* consumer = (PCB* )malloc(sizeof(PCB));

int main(int argc, char** argv) {
	int tmp;
	printf("Welcome to Producer-consumer simulation!\nPlease input the number of total products: ");
	scanf("%d", &to_produce);
	to_consume = to_produce;
	init();
	schedule();
	getchar();
	return 0;
}
