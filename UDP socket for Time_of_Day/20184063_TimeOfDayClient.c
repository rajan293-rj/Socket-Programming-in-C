//Rajan Kumar Jaiswal
//20184063
//cs B
//qn 2 : 20184063_TimeOfDayClient.c  program

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define MAXSIZE 1024 


int main(int argc  ,char *argv[]) { 
	int sockfd,PORT; 
	char buffer[MAXSIZE]; 
	char *request_message = "what's the time?"; 
	struct sockaddr_in servaddr; 

 
    //creating socket returns socket descriptor that you can use in later system calls, or -1 on error.
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Forcefully attaching socket the port 4043
	PORT  = atoi(argv[2]);
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	
	//argv[1] is address of server machine presentable to network
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) { 
		printf("\nAddress not supported \n"); 
		return -1; 
	} 
	//printf("server %d",ntohs(servaddr.sin_port));
	int n, len; 
	
	sendto(sockfd, (const char *)request_message , strlen(request_message), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
	printf("Request has been sent to SERVER!!\n"); 
		
	n = recvfrom(sockfd, (char *)buffer, MAXSIZE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
	buffer[n] = '\0'; 
	printf("REPLY FROM SERVER (-_-) : %s\n", buffer); 

	close(sockfd); 
	return 0; 
} 


