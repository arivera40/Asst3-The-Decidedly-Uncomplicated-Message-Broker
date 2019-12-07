#ifndef utilities_H
#define utilities_H

typedef struct _node{
	//char* name;
	//double value;
	//int serving;
	//struct _node* next;
} node;

typedef struct _Arguments{
	int serverSocket;
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
