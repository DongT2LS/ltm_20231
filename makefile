all: server client

server: server.c authentication/authentication.c game.c model/account.c
	gcc -o server authentication/authentication.c server.c game.c model/account.c -pthread

client: client.c
	gcc client.c -o client 

.PHONY: clean

clean:
	rm -f server client