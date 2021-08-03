//RAJAN KUMAR JAISWAL
//20184063
//CS B
// QN 1 : Server C code to reverse a string by sent from client 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 

#define PORT 3128

int main() 
{ 
	int sockfd, new_socket, valread; 
	struct sockaddr_in address; 
	char str[100]; 
	int addrlen = sizeof(address); 
	char buffer[1024] = { 0 }; 
	

	// Creating socket file descriptor 
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	 { 
		perror("Error opening Socket : socket failed "); 
		exit(EXIT_FAILURE); 
	} 

	//getting ready server address
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons(PORT); 

	//binding socket to server address
	if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0)
	 { 
		perror("ERROR !! bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	// puts the server socket in passive mode 
	if (listen(sockfd, 3) < 0) 
	{ 
		perror("ERROR !! listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) 
	{ 
		perror("ERRO !! accept"); 
		exit(EXIT_FAILURE); 
	} 

	// read string send by client 
	valread = read(new_socket, str, sizeof(str)); 
	int i, j, temp; 
	int l = strlen(str); 

	printf("\n String received from client:%s\n", str); 

	// loop to reverse the string 
	for (i = 0, j = l - 1; i < j; i++, j--) { 
		temp = str[i]; 
		str[i] = str[j]; 
		str[j] = temp; 
	} 

	// send reversed string to client 
	// by send system call 
	send(new_socket, str, sizeof(str), 0); 
	printf("\n reversed string sent to client : %s\n",str); 

	return 0; 
} 



