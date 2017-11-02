#include "client.h"

int main(int argc, char **argv)
{
// write someting here...
	char work;
	int EXIT = 0;

	//create a socket
	int sockfd = 0;
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if(sockfd == -1) {
		printf("Fail to create a socket");
	}

	//socket link
	struct sockaddr_in info;
	bzero(&info,sizeof(info));
	info.sin_family = PF_INET;

	//access localhost
	info.sin_addr.s_addr = inet_addr("127.0.0.1");
	info.sin_port = htons(8700);

	int err = connect(sockfd,(struct sockaddr*)&info,sizeof(info));
	if(err == -1) {
		printf("Connection error");
	}

	//send a message
	char message[]= {"Hi! this is client~"};
	char receivefromServer[1000] = {};
	//while(!EXIT) {
	/****************************
	        User Interface
	****************************/
	/*	printf("======================================================");
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
		scanf("%c",&work); */
	send(sockfd,message,sizeof(message),0);
	recv(sockfd,receivefromServer,sizeof(receivefromServer),0);
	printf("%s",receivefromServer);
	//  }
	//}
	close(sockfd);
	return 0;
}

