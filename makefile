all: server client

server: server.c authentication.c
	gcc -o server authentication.c server.c -pthread

client: client.c
	gcc client.c -o client 

.PHONY: clean

clean:
	rm -f server client