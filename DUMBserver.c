#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/time.h>
#include <signal.h>
#include <semaphore.h>
#include "utilities.h"

int index = 0;
pthread_t threads[256];
int sockets[256];
int killFlag;
//Server forms the listener socket while client reaches out to the server
void listener(void* socket_fd){
	
}

void killHandler(void* args){	//args contains: serverSocket, serverAddress, addressSize
	//signal to end program incomplete	
	struct sigaction flag;	
	struct itimerval timer;
	memset(&flag, 0, sizeof(flag));
	flag.sa_handler = //flag handler function
	sigaction(SIGALRM, &alarm, NULL);	//SIGALRM stored in alarm, previous alarm stored in NULL bc no longer needed
	timer.it_value.tv_sec = 15;
	timer.it_value.tv_usec = 15;
	timer.it_interval.tv_sec = 15;
	timer.it_interval.tv_usec = 15;
	setitimer(ITIMER_REAL, &timer, NULL);
	//--------------------------------
	
}

int main(int argc, char** argv){
	if(argc != 2){
		printf("Error: Only port number required!\n");
		return 0;
	}
	
	int serverSocket;
	int clientSocket;
	struct sockaddr_in serverAddr;
	int addrlen = sizeof(serverAddr);
	int option = 1;	//boolean value used to specify if bind() should allow reuse of local addresses (USED in conjunction with SO_REUSEADDR)

	//**Create socket**
	if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}
	
	//**Set rules for new socket**
	if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option))){	//setsockopt returns -1 if error
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	//**Set socket ruleset**
	//Address family = Internet
	serverAddr.sin_family = AF_INET;//Sockets created with the socket()function are inititally unnamed they are identified by their address family
	//INADDR_ANY is used when you don't need to bind a socket to a specific IP
	//When you use this value as the address when calling bind(), the socket accepts connections to all IPs machine
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	//Set port number, using htons function to use proper byte order
	serverAddr.sin_port = htons(atoi(argv[1]));

	//**bind socket to given port**
	if(bind(serverSocket, (struct sockaddr*)&serverAddr, addrlen) == -1){	//bind() shall return 0; otherwise, -1 shall be returned for error
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}
	
	//**mark socket as listening**
	if(listen(serverSocket, 5) < 0){
		perror("Listen");
		exit(EXIT_FAILURE);
	}
	
	Arguments* acceptArgs = (Arguments*)malloc(sizeof(Arguments));
	acceptArgs->serverSocket = serverSocket;
	acceptArgs->serverAddr = (struct sockaddr*)&serverAddr;
	acceptArgs->addrSize = (socklen_t*)&addrlen;
	pthread_t mainThread;	//may decide to change name
	if(pthread_create(&mainThread, NULL, (void*)killHandler, (void*)acceptArgs) != 0){
		//error
	}
/*	while(1){
		if((clientSocket = accept(serverSocket, acceptArgs->serverAddr, acceptArgs->addrSize)) < 0){
			perror("Accept session thread creation");
			exit(EXIT_FAILURE);
		}
		commandArgs args = (commandArgs*)malloc(sizeof(commandArgs);
		args->clientSocket = clientSocket;
		if(pthread_create(&threads[index], NULL, (void*)commands, (void*)args) != 0){
			perror("Listener");
			exit(EXIT_FAILURE);
		}
		index++;
	}	*/
	
}
