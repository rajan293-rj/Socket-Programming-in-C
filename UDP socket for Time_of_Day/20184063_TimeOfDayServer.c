//Rajan Kumar Jaiswal
//20184063
//cs B
//qn 2 : 20184063_TimeOfDayServer.c  program

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include<time.h>
#define PORT  4043
#define MAXSIZE 1024 


int main() { 
	int sockfd; 
	char buffer[MAXSIZE]; 
	char message_toclient[30] = ""; 
	struct sockaddr_in servaddr, cliaddr; 
	
   //CREATING SOCKET
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET;           // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	 
	 printf("SERVER IS READY !!  Waiting for connection....\n");
	
	int len, n; 

	len = sizeof(cliaddr); 

	n = recvfrom(sockfd, (char *)buffer, MAXSIZE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 

	buffer[n] = '\0'; 
	printf("Request from Client : %s\n", buffer); 
	time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(message_toclient,"%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	sendto(sockfd, (const char *)message_toclient,  strlen(message_toclient), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
			
	printf("response has been sent to the Client \n"); 
	
	return 0; 
} 


