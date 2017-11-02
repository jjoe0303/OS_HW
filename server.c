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
		//openFile(fin,pid,buffer);
		listAll();
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

void listAll()
{
	DIR * dir = opendir("/proc");
	struct dirent *pidname;
	char base[1000];
	memset(base,'\0',sizeof(base));
	if((dir=opendir("/proc")) == NULL) {
		perror("Open dir error...");
		exit(1);
	}

	while((pidname=readdir(dir)) != NULL) {
		if(strcmp(pidname->d_name,".")==0 || strcmp(pidname->d_name,"..")==0)
			continue;
		else if(pidname->d_type == 4 && isdigit(pidname->d_name[0])) {
			//memset(base,'\0',sizeof(base));
			strcat(base,pidname->d_name);
			strcat(base,",");
			// printf("%s\n",base);
		}
	}
	printf("%s\n",base);
	closedir(dir);
	return;
}


