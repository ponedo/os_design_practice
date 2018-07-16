#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, pid;
	pid = fork();
	if (pid < 0)
	    printf("Fork, failed!");
	else if (pid == 0)
	{
		//child process
		for (i=0; i<5; i++)
		    printf("Hello from child! (No. %d)\n", i);
		exit(0);
	}
	else
	{
		//parent process
		for (i=0; i<5; i++)
		    printf("Hello from parent! (No. %d)\n", i);
		exit(0);
	}
	return 0; 
}
