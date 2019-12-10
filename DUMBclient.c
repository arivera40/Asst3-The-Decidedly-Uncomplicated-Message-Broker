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

void checkError(int sock, int command);
void commands(int sockfd);

void commands(int sockfd){
	int work = 0;
	while(work == 0){
		char* commandInput = "";
		char mailboxName[26];
		char serverCommands[4096];
		char message[4000];
		int recvSocket = 0;
		
		printf("Please type in command");
		scanf("%s", commandInput); //scans in input and adds correct #of bytes and add '\0' at the end
		if(strcmp("quit", commandInput) == 0){
			strcpy(serverCommands, "GDBYE");
			send(sockfd, serverCommands,strlen(serverCommands), 0);
			work = 1;
			
		}else if(strcmp("create", commandInput) == 0){ // create message
			printf("What is the name of the mailbox you want to create?\n");
			read(0,mailboxName,sizeof(mailboxName));
			strcpy(serverCommands, "CREAT!");
			strcpy(&serverCommands[6], mailboxName);
			send(sockfd, serverCommands, sizeof(serverCommands), 0);
			recvSocket = read(sockfd, serverCommands, strlen(serverCommands));
			checkError(recvSocket, 1);
		}else if(strcmp("open", commandInput) == 0){ // open mailbox
			printf("What is the name of the mailbox you want to open?\n");
			read(0, mailboxName, sizeof(mailboxName));
			strcpy(serverCommands, "OPNBX!");
			strcpy(&serverCommands[6], mailboxName);
			send(sockfd, serverCommands, strlen(serverCommands), 0);
			recvSocket = read(sockfd, serverCommands, strlen(serverCommands));
			checkError(recvSocket,2);
		}else if(strcmp("next", commandInput) == 0){ // get next message
			strcpy(serverCommands,"NXTMG!");
			recvSocket = send(sockfd, serverCommands, strlen(serverCommands), 0);
			checkError(recvSocket, 3); //
		}else if(strcmp("put", commandInput)== 0){ // put message
			printf("What message do you want to put?");
			read(0, message, sizeof(message));
			int sizeOfMessage = sizeof(message);
			char number [15];
			sprintf(number,"%d", sizeOfMessage); //converts num to string
			int j =0;
			while(number[j] != '\0'){
				j++;
			}
			number[j] = '!';
			//include size of message
			strcpy(serverCommands, "PUTMG!");
			strcpy(&serverCommands[6],number);
			strcpy(&serverCommands[6+sizeof(number)], message);
			send(sockfd, serverCommands, strlen(serverCommands), 0);
			recvSocket = read(sockfd, serverCommands, strlen(serverCommands));
			checkError(recvSocket, 4);
		}else if(strcmp("delete", commandInput) == 0){ // delete mailbox
			printf("Which mailbox do you want to delete?");
			read(0, mailboxName, sizeof(mailboxName));
			strcpy(serverCommands, "DELBX!");
			strcpy(&serverCommands[6], mailboxName);
			send(sockfd, serverCommands, strlen(serverCommands), 0);
			recvSocket = read(sockfd, serverCommands, strlen(serverCommands));
			checkError(recvSocket, 5);
		}else if(strcmp("close", commandInput) == 0){ //close mailbox
			printf("Which mailbox do you want to close?");
			read(0, mailboxName, sizeof(mailboxName));
			strcpy(serverCommands, "CLSBX!");
			strcpy(&serverCommands[6], mailboxName);
			send(sockfd, serverCommands, strlen(serverCommands), 0);
			recvSocket = read(sockfd, serverCommands, strlen(serverCommands));
			checkError(recvSocket, 6);
		} else if(strcmp("help", commandInput) == 0){
			printf("Here are the commands you can type");
			printf("quit\ncreate\ndelete\nopen\nclose\nnext\nput\n");
		}else{
			printf("Unknown command. Please try again");
		}
		
	}
	return;
}

void checkError(int sock, int command){
	char messagefromServer[8];
	read(sock, messagefromServer, 3);
	char errorName[5];
	if(strcmp("OK!", messagefromServer)== 0){
		printf(" Command successfully performed\n");
	}else{
		strcpy(errorName, &errorName[3]);
		if(command==1){
			if(strcmp("EXIST", errorName) == 0){ // create
				printf("Error: Username already exists\n");
				return;
			}else{
				printf("Error, your message is broken or malformed\n");
				return;
			}
		}
		if(command == 2){
			if (strcmp("NEXST", errorName)== 0){ //openbox
				printf("Box does not exist, cannot be opened\n");
				return;
			}else if(strcmp("OPEND", errorName)==0){
				printf("Box already ope, cannot be opened\n");
				return;
			}else{
				printf("Error, your message is broken or malformed\n");
				return;
			}
		}
		if(command == 3){
			if (strcmp("EMPTY", errorName)== 0){//nxtmg
				printf("No messages left in the message box\n");
				return;
			}else if(strcmp("NOOPN", errorName)==0){
				printf("Message box not open or message box does not exist\n");
				return;
			}else{
				printf("Error, your message is broken or malformed\n");
				return ;
			}
		if(command == 4){
			if(strcmp("NOOPN", errorName)==0){ //putmg
				printf("Message box not open or message box does not exist\n");
				return;
			}else{
				printf("Error, your message is broken or malformed\n");
				return;
			}
		if(command == 5){ 
			if(strcmp("NEXST", errorName)==0){ //delbx
				printf("Message box does not exist\n");
				return;
			}else if(strcmp("OPEND", errorName)==0){ 
				printf("Message box currently opened, cannot delete while opened\n");
				return;
			}else if(strcmp("NOTMT", errorName)==0){ 
				printf("Message box still has messages, cannot delete\n");
				return ;
			}else{
				printf("Error, your message is broken or malformed\n");
				return;
			}
		if(command == 6){
			if(strcmp("NOOPN", errorName)==0){ //clsbx
				printf("No open message box, cannot close\n");
				return;
			}else {
				printf("Error, your message is broken or malformed\n");
				return;
			}
		}
	}
	
}


int main(int argc, char** argv){

        int fail = 0;
        struct sockaddr_in address; 
        //check for error, if error occurs more than 3 times, shut down
	if(argc != 3){
	        printf("Error! Type in correct number of arguments, IP address/ hostname and port number\n");
	        fail++; 
	}
	if(fail != 0){
	        while(argc != 3 && fail <3){
	                printf("Error! Type in correct number of arguments, IP address/ hostname and port number\n");
	                fail++;
	        }
                if(fail == 3){
                        printf("Error: too many failed attempts, Goodbye\n");
                        return 0;
                }
	}
	
	
	//int portNum = atoi(argv[2]);
	int sockfd = 0;
	
	//create socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
	        printf("Error creating socket\n");
	        return -1;
	}
	
	//initializing server address
	//bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(atoi(argv[2]));
	address.sin_addr.s_addr = inet_addr(argv[1]);
	
	//check for connection errors
	if(connect(sockfd, (struct sockaddr*)&address, sizeof(address))<0){
		printf("connection failed\n");
		return -1;
	}else{
		printf("Connection successful!\n");
	}
	
	commands(sockfd);
	
	return 0;
}
