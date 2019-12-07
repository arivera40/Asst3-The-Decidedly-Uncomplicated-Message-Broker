#ifndef utilities_H
#define utilities_H

typedef struct _Node{
	int clientSocket;
	int threadID;
	struct _node* next;
} Node;

typedef struct _Arguments{
	int clientSocket;
	struct sockaddr* serverAddr;
	socklen_t* addrSize;
} Arguments;

typedef struct _commandArgs{
	int clientSocket;
} commandArgs;

typedef struct _sfdPill{
	//int sfd;
} sfdPill;

#endif
