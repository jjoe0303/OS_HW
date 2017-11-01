#include "server.h"

int main(int argc, char **argv)
{
// write someting here...
    FILE *fin;
    char buffer[2000];
    char pid[50];
    printf("pid?");
    scanf("%s",&pid);
    openFile(fin,pid,buffer);
	return 0;

}

void openFile(FILE *fin , char pid[] ,char buffer[]){
    /*concat the address*/
    char address[70];
    strcat(address,"/proc/");
    strcat(address,pid);
    strcat(address,"/status");

    /*open file*/
    fin = fopen(address,"r");
    while(fgets(buffer,100,fin)!= NULL){
             printf("%s",buffer);
    }
    
}

