//RAJAN KUMAR JAISWAL
//20184063
//CS B

// qn 2 : C client code to send an expression to a server and receive evaluated result from server

#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <netdb.h> 

int PORT;

// Driver code 
int main(int argc , char *argv[]) 
{ 
struct addrinfo hints, *res, *p;
int status;
char ipstr[INET6_ADDRSTRLEN];

if (argc != 3)
 {
fprintf(stderr,"usage: show ip hostname\n");
return 1;
}

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
hints.ai_socktype = SOCK_STREAM;
if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
return 2;
}
printf("IP address for %s  at port %s:\n\n", argv[1],argv[2]);



for(p = res;p != NULL; p = p->ai_next) 
{
void *addr;
char *ipver;
 // get the pointer to the address itself,
// different fields in IPv4 and IPv6:

if (p->ai_family == AF_INET)
{ // IPv4
struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
addr = &(ipv4->sin_addr);
ipver = "IPv4";
} 
inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
printf(" %s: %s %d\n", ipver, ipstr, PORT);
}



        freeaddrinfo(res); // free the linked list
        
        PORT  = atoi(argv[2]);
        
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char str[100]; 

	printf("\nInput the string:"); 
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

	/*Convert IPv4 and IPv6 addresses from text to binary form 
	127.0.0.1 is localhost IP address, this address should be  your system local host IP address 
	*/
	
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) 
	{ 
		printf("\nAddress not supported \n"); 
		return -1; 
	} 

	// connect to  the socket 
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nERROR !! socket Connection Failed \n"); 
		return -1; 
	} 

	int l = strlen(str); 

	// send string to server side  for evaluation
	send(sock, str, sizeof(str), 0); 

	// read result sent by server 
	valread = read(sock, str, l); 

	printf("Evaluated Result received from SERVER : %s\n", str); 

	return 0; 
	
} 

