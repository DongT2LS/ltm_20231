all: server client

server: server.c authentication.c game.c
	gcc -o server authentication.c server.c game.c -pthread

client: client.c
	gcc client.c -o client 

.PHONY: clean

clean:
	rm -f server client