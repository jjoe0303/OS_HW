#include "client.h"

int main(int argc, char **argv)
{
// write someting here...
	char work;
	int EXIT = 0;
	while(!EXIT) {
		/****************************
		        User Interface
		****************************/
		printf("======================================================");
		printf("\n(a)list all process ids\n");
		printf("(b)thread's IDs\n");
		printf("(c)child's PIDs\n");
		printf("(d)process name\n");
		printf("(e)state of process(D,R,S,T,t,W,X,Z)\n");
		printf("(f)command line of excuting process(cmdline)\n");
		printf("(g)parent's PID\n");
		printf("(h)all ancients of PIDs\n");
		printf("(i)virtual memory size(VmSize)\n");
		printf("(j)physical memory size(VmRSS)\n");
		printf("(k)exit\n");
		printf("which?");
		scanf("%c",&work);
	}
	return 0;
}

