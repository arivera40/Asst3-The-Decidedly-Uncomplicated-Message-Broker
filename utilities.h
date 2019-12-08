#ifndef utilities_H
#define utilities_H

typedef struct _Node{
	int clientSocket;
	int threadID;
	struct _node* next;
} Node;

typedef struct _Message{
	char* text;
	int length;
	struct _Message* next_msg;
} Message;

typedef struct _messageBox{
	char *name;
	int open;
	struct _Message message;
	struct _messageBox* next_box;
} _messageBox;

typedef struct _commandArgs{
	int clientSocket;
} commandArgs;


#endif
