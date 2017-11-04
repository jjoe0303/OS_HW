#include "server.h"

int main(int argc, char **argv)
{
	//	//declare variable
	//	FILE *fin;
	//	char buffer[100];
	//	char value[100];
	//	char pid[50];
	//	char base[1000];

	//create a socket
	//char inputBuffer[1000]= {};
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
	serverinfo.sin_port = htons(59487);

	//Bind()
	if(bind(sockfd,(struct sockaddr *)&serverinfo,sizeof(serverinfo)) < 0) {
		perror("Bind failed\n");
		return 1;
	} else {
		printf("Bind Done!\n");
	}

	//Listen()
	listen(sockfd,100);

	printf("Waiting for connections...\n");
	pthread_t thread_id;
	while((forClientSockfd = accept(sockfd,(struct sockaddr *)&clientinfo,
	                                &addrlen))) {
		printf("Connection Accept...\n");
		if(pthread_create(&thread_id,NULL,pthread_handler,
		                  (void *)&forClientSockfd) < 0) {
			perror("Couldn't create thread...\n");
			return 1;
		}
		printf("Handler assigned~\n");
	}

	if(forClientSockfd < 0) {
		perror("accept failed!\n");
		return 1;
	}

	return 0;
}


void getPid(char  pid[],char inputBuffer[])
{
	int i;
	char array[50];
	//memset(pid,'\0',sizeof(pid));
	memset(array,'\0',sizeof(array));
	//printf("buffersize=%d\n",sizeof(inputBuffer));
	for(i=0; i<sizeof(inputBuffer); ++i) {
		if(inputBuffer[i+1]=='\0') break;
		array[i]=inputBuffer[i+1];
		sprintf(pid,"%s%c",pid,array[i]);
		//strcat(pid,pid[i]);
		//printf("pid[%d]=%c , pid = %s \n",i,array[i],pid);
	}

	return;
}

void scanString(char buffer[],char value[])
{
	int i,j=0;
	int isValue = 0;
	for(i=0; i<strlen(buffer); ++i) {
		//printf("buffer[%d]=%c\n",i,buffer[i]);
		if(buffer[i]=='\n') break;
		if(buffer[i]==':' && isValue == 0) {
			isValue=1;
			continue;
		}
		if(isValue && buffer[i]!=' ' && buffer[i]!='\t' && buffer[i]!='\0') {
			value[j]=buffer[i];
			//printf("value[%d]=%c\n",j,value[j]);
			j++;
		}

	}
	return;
}

void getCmdline(FILE *fin,char value[])
{
	memset(value,'\0',sizeof(value));
	fin = fopen("/proc/self/cmdline","r");
	fgets(value,100,fin);

	return;
}

void findAncient(FILE *fin,char pid[],char buffer[],char work,char value[],
                 char ppid[])
{
	int isFirst=1;
	while(strcmp(pid,"0")!=0) {
		openFile(fin,pid,buffer,'g',value);
		//printf("ppid=%s\n",value);
		if(isFirst) {
			sprintf(ppid,"%s",value);
		} else if(!isFirst) {
			sprintf(ppid,"%s,%s",ppid,value);
		}
		memset(pid,'\0',sizeof(pid));
		sprintf(pid,"%s",value);
		memset(value,'\0',sizeof(value));
		isFirst=0;
	}
}

void openFile(FILE *fin, char pid[],char buffer[],char work,char value[])
{
	memset(buffer,'\0',sizeof(buffer));
	memset(value,'\0',sizeof(value));
	/*concat the address*/
	char address[70]="";
	strcat(address,"/proc/");
	strcat(address,pid);
	strcat(address,"/status");
	int isFind = 0;
	//printf("%s\n",address);
	/*open file*/
	fin = fopen(address,"r");
	while(fgets(buffer,40,fin)!= NULL) {
		memset(value,'\0',sizeof(value));
		if(buffer[0]=='N' && buffer[1]=='a' && buffer[2]=='m' && buffer[3]=='e'
		   && work =='d') {
			scanString(buffer,value);
			isFind=1;
			break;
		} else if(buffer[0]=='S' && buffer[1]=='t' && buffer[2]=='a' && buffer[3]=='t'
		          && buffer[4]=='e' && work=='e') {
			scanString(buffer,value);
			isFind=1;
			break;
		} else if(buffer[0]=='P' && buffer[1]=='P' && buffer[2]=='i' && buffer[3]=='d'
		          && work=='g') {
			scanString(buffer,value);
			isFind=1;
			break;
		} else if(buffer[0]=='V' && buffer[1]=='m' && buffer[2]=='S' && buffer[3]=='i'
		          &&buffer[4]=='z' && buffer[5]=='e'&& work=='i') {
			scanString(buffer,value);
			isFind=1;
			break;
		} else if(buffer[0]=='V' && buffer[1]=='m' && buffer[2]=='R' && buffer[3]=='S'
		          &&buffer[4]=='S' && work=='j') {
			scanString(buffer,value);
			isFind=1;
			break;
		}
	}
	if(!isFind) {
		strcpy(value,"Not found!!");
	}
	fclose(fin);
}


void findChild(FILE *fin, char pid[],char buffer[],char work,char value[],
               char base[])
{
	DIR * dir = opendir("/proc");
	struct dirent *pidname;
	int nonFirst=0;
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
			openFile(fin,pidname->d_name,buffer,'g',value);
			if(strcmp(value,pid) == 0) {
				if(!nonFirst) {
					sprintf(base,"%s",pidname->d_name);
					nonFirst=1;
				} else {
					sprintf(base,"%s,%s",base,pidname->d_name);
				}
			}
			memset(value,'\0',sizeof(value));
			// printf("%s\n",base);
		}
	}
	//	printf("%s\n",base);
	closedir(dir);
	return;



}

void listAll(char base[])
{
	DIR * dir = opendir("/proc");
	struct dirent *pidname;
	//char base[1000];
	//memset(base,'\0',sizeof(base));
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
	//	printf("%s\n",base);
	closedir(dir);
	return;
}

void *pthread_handler(void *sockfd)
{
	int sock = *(int*)sockfd;
	FILE *fin;
	char buffer[256];
	char value[256];
	char pid[50];
	char ppid[256];
	char base[1000];
	char inputBuffer[1000]= {};

	/*mem initialize*/
	memset(inputBuffer,'\0',sizeof(inputBuffer));
	memset(buffer,'\0',sizeof(buffer));
	memset(value,'\0',sizeof(value));
	memset(pid,'\0',sizeof(pid));
	memset(ppid,'\0',sizeof(ppid));
	memset(base,'\0',sizeof(base));

	//forClientSockfd = accept(sockfd,(struct sockaddr *)&clientinfo,&addrlen);
	//send(forClientSockfd,message,sizeof(message),0);
	recv(sock,inputBuffer,sizeof(inputBuffer),0);
	printf("Get:%s\n",inputBuffer);

	//listAll(base);
	//printf("%s\n",base);
	if(strcmp(inputBuffer,"a") == 0) {
		listAll(base);
		send(sock,base,sizeof(base),0);
	}

	else if(inputBuffer[0] == 'b') {
		sprintf(value,"%lu",pthread_self());
		printf("value=%s\n",value);
		send(sock,value,sizeof(value),0);
	}

	else if(inputBuffer[0] == 'c') {
		getPid(pid,inputBuffer);
		findChild(fin,pid,buffer,inputBuffer[0],value,base);
		if(strcmp(base,"") == 0) {
			sprintf(base,"%s","Not found!!");
		}

		printf("value=%s\n",base);
		send(sock,base,sizeof(base),0);

	}

	else if(inputBuffer[0] == 'd') {
		getPid(pid,inputBuffer);
		//printf("%s\n",pid);
		//cleanValue(value);
		openFile(fin,pid,buffer,inputBuffer[0],value);
		printf("value=%s\n",value);
		send(sock,value,sizeof(value),0);
	}

	else if(inputBuffer[0] == 'e') {
		getPid(pid,inputBuffer);
		openFile(fin,pid,buffer,inputBuffer[0],value);
		printf("value=%s\n",value);
		send(sock,value,sizeof(value),0);
	}

	else if(inputBuffer[0] == 'f') {
		getCmdline(fin,value);
		printf("value=%s\n",value);
		send(sock,value,sizeof(value),0);
	}

	else if(inputBuffer[0] == 'g') {
		getPid(pid,inputBuffer);
		openFile(fin,pid,buffer,inputBuffer[0],value);
		printf("value=%s\n",value);
		send(sock,value,sizeof(value),0);
	}

	else if(inputBuffer[0] == 'h') {
		getPid(pid,inputBuffer);
		findAncient(fin,pid,buffer,inputBuffer[0],value,ppid);
		printf("value=%s\n",ppid);
		send(sock,ppid,sizeof(ppid),0);
	}


	else if(inputBuffer[0] == 'i') {
		getPid(pid,inputBuffer);
		openFile(fin,pid,buffer,inputBuffer[0],value);
		printf("value=%s\n",value);
		send(sock,value,sizeof(value),0);
	}

	else if(inputBuffer[0] == 'j') {
		getPid(pid,inputBuffer);
		openFile(fin,pid,buffer,inputBuffer[0],value);
		printf("value=%s\n",value);
		send(sock,value,sizeof(value),0);
	}
	return;
}
