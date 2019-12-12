all: client serve

client:
	gcc -g -Wall -Werror -fsanitize=address -o DUMBclient DUMBclient.c -lpthread

serve:
	gcc -g -Wall -Werror -fsanitize=address -o DUMBserve DUMBserver.c -lpthread

clean:
	rm DUMBclient rm DUMBserve
