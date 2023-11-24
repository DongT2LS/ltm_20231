all: server client

server: server.c
	gcc -o server authentication/authentication.c server.c game.c -pthread

client: client.c
	gcc client.c -o client 

.PHONY: clean

clean:
	rm -f server client