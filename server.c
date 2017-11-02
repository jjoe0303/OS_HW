#include "server.h"

int main(int argc, char **argv)
{
// write someting here...
	FILE *fin;
	char buffer[100];
	char pid[50];
	char base[1000];

	//create a socket
	char inputBuffer[1000]= {};
	char message[] = {"Hi!this is server.\n"};
	int sockfd = 0,forClientSockfd=0;
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if(sockfd == -1) {
		printf("Fail to create a socket...");
	}

	else {
		printf("Socket created\n");
	}
	//socket link
	struct sockaddr_in serverinfo,clientinfo;
	int addrlen = sizeof(clientinfo);
	bzero(&serverinfo,sizeof(serverinfo));

	serverinfo.sin_family = PF_INET;
	serverinfo.sin_addr.s_addr = INADDR_ANY;
	serverinfo.sin_port = htons(8700);
	bind(sockfd,(struct sockaddr *)&serverinfo,sizeof(serverinfo));
	listen(sockfd,5);

	while(1) {
		forClientSockfd = accept(sockfd,(struct sockaddr *)&clientinfo,&addrlen);
		send(forClientSockfd,message,sizeof(message),0);
		recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
		printf("Get: %s\n",inputBuffer);
	}



	/*while(1) {
		printf("pid?");
		scanf("%s",&pid);
		//openFile(fin,pid,buffer);
		listAll();
	}*/
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

void listAll(char *base[])
{
	DIR * dir = opendir("/proc");
	struct dirent *pidname;
	//char base[1000];
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


