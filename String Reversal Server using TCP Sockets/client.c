//RAJAN KUMAR JAISWAL
//20184063
//CS B
//qn 1 : C client code to send string to reverse 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 

#define PORT 3128

// Driver code 
int main(int argc , char *argv[]) 
{ 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char str[100]; 

	printf("\nEnter the string : "); 
	scanf("%[^\n]s", str); 

	char buffer[1024] = { 0 }; 

	// Creating socket file descriptor 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 

	//argv[1] is address of server machine
	if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) 
	{ 
		printf("\n ERROR !! address\n"); 
		return -1; 
	} 

	// connect the socket 
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	 { 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 

	int l = strlen(str); 

	// send string to server side 
	send(sock, str, sizeof(str), 0); 

	// read string sent by server 
	valread = read(sock, str, l); 

	printf("FROM SERVER : %s\n", str); 

	return 0; 
	
} 



