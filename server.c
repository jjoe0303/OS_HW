#include "server.h"

int main(int argc, char **argv)
{
	// write someting here...
	FILE *fin;
	char buffer[100];
	char value[100];
	char pid[50];
	char base[1000];

	//create a socket
	char inputBuffer[1000]= {};
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
	bind(sockfd,(struct sockaddr *)&serverinfo,sizeof(serverinfo));
	listen(sockfd,5);

	while(1) {
		/*mem initialize*/
		memset(inputBuffer,'\0',sizeof(inputBuffer));
		memset(buffer,'\0',sizeof(buffer));
		memset(value,'\0',sizeof(value));
		memset(pid,'\0',sizeof(pid));
		memset(base,'\0',sizeof(base));

		forClientSockfd = accept(sockfd,(struct sockaddr *)&clientinfo,&addrlen);
		//send(forClientSockfd,message,sizeof(message),0);
		recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
		printf("Get:%s\n",inputBuffer);

		//listAll(base);
		//printf("%s\n",base);
		if(strcmp(inputBuffer,"a") == 0) {
			listAll(base);
			//       printf("%s\n",base);
			send(forClientSockfd,base,sizeof(base),0);
		}

		else if(inputBuffer[0] == 'd') {
			getPid(pid,inputBuffer);
			//printf("%s\n",pid);
			//cleanValue(value);
			openFile(fin,pid,buffer,inputBuffer[0],value);
			printf("value=%s\n",value);
			send(forClientSockfd,value,sizeof(value),0);
		}

		else if(inputBuffer[0] == 'e') {
			getPid(pid,inputBuffer);
			openFile(fin,pid,buffer,inputBuffer[0],value);
			printf("value=%s\n",value);
			send(forClientSockfd,value,sizeof(value),0);
		}
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
		printf("buffer[%d]=%c\n",i,buffer[i]);
		if(buffer[i]=='\n') break;
		if(buffer[i]==':' && isValue == 0) {
			isValue=1;
			continue;
		}
		if(isValue && buffer[i]!=' ') {
			value[j]=buffer[i];
			printf("value[%d]=%c\n",j,value[j]);
			j++;
		}

	}
	return;
}

void openFile(FILE *fin, char pid[],char buffer[],char work,char value[])
{
	//memset(buffer,'\0',sizeof(buffer));
	//memset(value,'\0',sizeof(value));
	/*concat the address*/
	char address[70]="";
	strcat(address,"/proc/");
	strcat(address,pid);
	strcat(address,"/status");
	//printf("%s\n",address);
	/*open file*/
	fin = fopen(address,"r");
	while(fgets(buffer,40,fin)!= NULL) {
		if(buffer[0]=='N' && buffer[1]=='a' && buffer[2]=='m' && buffer[3]=='e'
		   && work =='d') {
			scanString(buffer,value);
			break;
		} else if(buffer[0]=='S' && buffer[1]=='t' && buffer[2]=='a' && buffer[3]=='t'
		          && buffer[4]=='e' && work=='e') {
			scanString(buffer,value);
			break;
		}
	}
	fclose(fin);
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


