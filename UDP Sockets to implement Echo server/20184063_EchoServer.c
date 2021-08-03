//Rajan Kumar Jaiswal
//20184063
//cs B
//qn1 : 20184063_EchoServer.c program

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define PORT 4043

int main()
{
	int sockfd;
	char msg[1000];
	struct sockaddr_in servaddr,cliaddr;
	
	//creating socket 
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("ERROR !!Socket cannot Be Created");
		exit(0);
	}
	
	memset(&servaddr,0,sizeof(servaddr));
	memset(&cliaddr,0,sizeof(cliaddr));
	servaddr.sin_family=AF_INET;        //for INTERNET ADDRESS
	servaddr.sin_addr.s_addr=INADDR_ANY; //for ip of my pc
	servaddr.sin_port=htons(PORT);
	
	//binding socket to the server
	if(bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr)))
	{
		perror("ERROR !! Socket Cannot be binded");
		exit(0);
	}
	printf("Server started ... waiting for connection ...\n");
	int len,n;
	len=sizeof(cliaddr);
	n=recvfrom(sockfd,(char*)msg,1000,MSG_WAITALL,(struct sockaddr *)&cliaddr,(unsigned int*)&len);
	msg[n]='\0';
	printf("Received from Client - %s\n",msg);
	sendto(sockfd,(char*)msg,strlen(msg),MSG_CONFIRM,(const struct sockaddr * )&cliaddr,len);
	return 0;
}	
