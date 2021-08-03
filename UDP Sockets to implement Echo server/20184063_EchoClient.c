//Rajan Kumar Jaiswal
//20184063
//cs B
//qn1 : 20184063_Echoclient.c program

#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define PORT 4043

int main(int argc,char *argv[])
{
	int sockfd;
	if(argc==1)
	{
		perror("Give argument to echo");
		exit(0);
	}
	char *msg=argv[1];
	struct sockaddr_in serveraddr;
	
	//create socket
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("Socket not created");
		exit(0);
	}
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(PORT);
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	int n,len;
	sendto(sockfd,(const char*)msg,strlen(msg),MSG_CONFIRM,(const struct sockaddr *)&serveraddr,sizeof(serveraddr));
	printf("Message has been sent to server\n");
	n=recvfrom(sockfd,(char*)msg,1000,MSG_WAITALL,(struct sockaddr*)&serveraddr,&len);
	//msg[n]='\0';
	printf("Received from Server : %s\n",msg);
	return 0;
}
