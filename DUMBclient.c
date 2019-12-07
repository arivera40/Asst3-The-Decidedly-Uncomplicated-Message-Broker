#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>

int main(int argc, char**argv){
        int fail = 0;
        struct sockaddr_in address; 
        //check for error, if error occurs more than 3 times, shut down
	if(argv != 3){
	        printf("Error! Type in correct number of arguments, IP address/ hostname and port number");
	        fail++; 
	}
	if(fail != 0){
	        while(argv != 3 && fail <3){
	                printf("Error! Type in correct number of arguments, IP address/ hostname and port number");
	                fail++;
	        }
                if(fail == 3){
                        printf("Error: too many failed attempts, Goodbye");
                        return 0;
                }
	}
	
	char* address = argv[1];
	int portNum = atoi(argv[2]);
	int sockfd = 0;
	
	//create socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, O) < 0){
	        printf("Error creating socket");
	        return -1;
	}
	
	//initializing server address
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(portNum);
	address.sin_addr = inet_addr(address);
	
	//check for connection errors
	if(connect(sockfd, (struct sockaddr*)&address, sizeof(address))<0){
		printf("connection failed");
		return -1;
	}else{
		printf("Connection successful");
	}
	return 0;
}
