//RAJAN KUMAR JAISWAL
//20184063
//CS B

// qn 2  : Server C code to evaluate an expression sent from client

#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 

#define PORT 3128

   int isOperand(char c) { return (c >= '0' && c <= '9'); } 
  
   // utility function to find value of an operand 
   int value(char c) {  return (c - '0'); } 

//function to evaluate expression
  int evaluate(char *exp) 
  { 
    // Base Case: Given expression is empty 
    if (*exp == '\0')  return -1; 
  
    // The first character must be an operand, find its value 
    int res = value(exp[0]); 
  
    // Traverse the remaining characters in pairs 
    for (int i = 1; exp[i]; i += 2) 
    { 
        // The next character must be an operator, and 
        // next to next an operand 
        char opr = exp[i], opd = exp[i+1]; 
  
        // If next to next character is not an operand 
        if (!isOperand(opd))  return -1; 
  
        // Update result according to the operator 
        if (opr == '+')       res += value(opd); 
        else if (opr == '-')  res -= value(opd); 
        else if (opr == '*')  res *= value(opd); 
        else if (opr == '/')  res /= value(opd); 
  
        // If not a valid operator 
        else                  return -1; 
    } 
    return res; 
} 
int main() 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	char str[100]; 
	int addrlen = sizeof(address); 
	char buffer[1024] = { 0 }; 
	//char* hello = "Hello from server"; 

	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons(PORT); 

	//binding the socket to address
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) 
	{ 
		perror("ERROR !! bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	// puts the server socket in passive mode 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("ERROR in listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) 
	{ 
		perror("ERROR !! In accept"); 
		exit(EXIT_FAILURE); 
	} 

	// read string send by client 
	valread = read(new_socket, str, sizeof(str)); 
	int i, j, temp; 
	int l = strlen(str); 

	printf("\nString FROM CLIENT : %s\n", str); 

	// evaluating the string recieved from the client
	int res = evaluate(str); 
        sprintf(str, "%d", res);

	//send the evaluated value to the client
	send(new_socket, str, sizeof(str), 0); 
	printf("\n evaluated expression SENT to CLIENT : %s\n",str); 

	return 0; 
} 

