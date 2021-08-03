//Rajan Kumar Jaiswal
/*
Program for Connection-Oriented Iterative service in which server calculates the Net-salary of an 
Employee based on the following details sent by the client:
i) basic
ii) hra
iii) da
iv) pt
v) epf
vi) st
Formula for the Net Salary i : ( net salary =basic+hra+da-pt-epf-st).
Sample Input: The Client sends the salary details 1000 2000 3000 500 500 100
Sample Output Then it will return the complete salary after calculation 4900
*/

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        float basic, da, hra, pt, epf, st;
        
        //input required fields
        printf("Enter Basic Salary : ");
        scanf("%f",&basic);
        printf("Enter HRA : ");
        scanf("%f",&hra);
        printf("Enter DA : ");
        scanf("%f",&da);    
        printf("Enter pt : ");
        scanf("%f",&pt);    
        printf("Enter epf : ");
        scanf("%f",&epf);    
        printf("Enter st : ");
        scanf("%f",&st);    
        
        bzero(buff, sizeof(buff));
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
        float ans = basic+da+hra-(pt+epf+st);
        printf("The net salary is %f\n",ans);
        break;
    }
}
  
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
  
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
  
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
  
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
  

    func(sockfd);
  
    // close the socket
    close(sockfd);
}
