all: DUMBserver DUMBclient

DUMBserver: DUMBserver.c
	gcc -g -Wall -Werror -fsanitize=address -o DUMBserver
DUMBserver.c -pthread -lrt

DUMBclient: DUMBclient.c
	gcc -g -Wall -Werror -fsanitize=address -o DUMBclient
DUMBclient.c -pthread -lrt

clean:
	rm DUMBclient
	rm DUMBserver
