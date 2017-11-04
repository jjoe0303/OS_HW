#include "client.h"

int main(int argc, char **argv)
{
	// write someting here...
	char work;
	int EXIT = 0;

	while(!EXIT) {

		//create a socket
		int sockfd = 0;
		sockfd = socket(AF_INET,SOCK_STREAM,0);

		if(sockfd == -1) {
			printf("Fail to create a socket\n");
			exit(1);
		}

		//socket link
		struct sockaddr_in info;
		bzero(&info,sizeof(info));
		info.sin_family = PF_INET;

		//access localhost
		info.sin_addr.s_addr = inet_addr("127.0.0.1");
		info.sin_port = htons(59487);

		int err = connect(sockfd,(struct sockaddr*)&info,sizeof(info));
		if(err == -1) {
			printf("Connection error\n");
			exit(1);
		}

		//send a message
		char message[1000];
		char receivefromServer[1000] = {};
		memset(message,'\0',sizeof(message));
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
		getchar();
		if(work == 'a') {
			//memset(message,'\0',sizeof(message));
			//strcat(message,"a");
			sprintf(message,"%c",work);
			//printf("%s\n",message);
			send(sockfd,message,sizeof(message),0);
			recv(sockfd,receivefromServer,sizeof(receivefromServer),0);
			printf("%s\n",receivefromServer);
			close(sockfd);
		}

		else if(work == 'b') {
			sprintf(message,"%c",work);
			send(sockfd,message,sizeof(message),0);
			recv(sockfd,receivefromServer,sizeof(receivefromServer),0);
			printf("[Thread's id] %s\n",receivefromServer);
			close(sockfd);
		}

		else if(work == 'd') {
			printf("pid?");
			char pid[256];
			sprintf(message,"%c",work);
			gets(pid);
			strcat(message,pid);
			send(sockfd,message,sizeof(message),0);
			recv(sockfd,receivefromServer,sizeof(receivefromServer),0);
			//printf("haha\n");
			printf("[process name] %s\n",receivefromServer);
			close(sockfd);
		}

		else if(work == 'e') {
			printf("pid?");
			char pid[256];
			sprintf(message,"%c",work);
			gets(pid);
			strcat(message,pid);
			send(sockfd,message,sizeof(message),0);
			recv(sockfd,receivefromServer,sizeof(receivefromServer),0);
			printf("[State of process] %s\n",receivefromServer);
			close(sockfd);
		}

		else if(work == 'f') {
			sprintf(message,"%c",work);
			send(sockfd,message,sizeof(message),0);
			recv(sockfd,receivefromServer,sizeof(receivefromServer),0);
			printf("[Cmdline of executing process] %s\n",receivefromServer);
			close(sockfd);
		}

		else if(work == 'g') {
			printf("pid?");
			char pid[256];
			sprintf(message,"%c",work);
			gets(pid);
			strcat(message,pid);
			send(sockfd,message,sizeof(message),0);
			recv(sockfd,receivefromServer,sizeof(receivefromServer),0);
			printf("[parent's PID] %s\n",receivefromServer);
			close(sockfd);
		}


		else if(work == 'i') {
			printf("pid?");
			char pid[256];
			sprintf(message,"%c",work);
			gets(pid);
			strcat(message,pid);
			send(sockfd,message,sizeof(message),0);
			recv(sockfd,receivefromServer,sizeof(receivefromServer),0);
			printf("[virtual memory] %s\n",receivefromServer);
			close(sockfd);
		}

		else if(work == 'j') {
			printf("pid?");
			char pid[256];
			sprintf(message,"%c",work);
			gets(pid);
			strcat(message,pid);
			send(sockfd,message,sizeof(message),0);
			recv(sockfd,receivefromServer,sizeof(receivefromServer),0);
			printf("[physical memory] %s\n",receivefromServer);
			close(sockfd);

		} else if(work == 'k') {
			sprintf(message,"%s","Client Leave...");
			send(sockfd,message,sizeof(message),0);
			close(sockfd);
			EXIT = 1;
		}
	}
	return 0;
}

