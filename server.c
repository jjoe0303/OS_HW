#include "server.h"

int main(int argc, char **argv)
{
// write someting here...
	FILE *fin;
	char buffer[100];
	char pid[50];
	while(1) {
		printf("pid?");
		scanf("%s",&pid);
		openFile(fin,pid,buffer);
	}
	return 0;
}

void openFile(FILE *fin, char pid[],char buffer[])
{
	/*concat the address*/
	char address[70]="";
	strcat(address,"/proc/");
	strcat(address,pid);
	strcat(address,"/status");
	//printf("%s\n",address);
	/*open file*/
	fin = fopen(address,"r");
	while(fgets(buffer,100,fin)!= NULL) {
		if(buffer[0]=='P' && buffer[1]=='i' && buffer[2]=='d') {
			printf("%s",buffer);
		}
	}
	fclose(fin);
}

