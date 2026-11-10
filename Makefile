CC = gcc
CFLAGS = -Wall -Wextra

minigit: main.c lista.c lista.h
	$(CC) $(CFLAGS) -o minigit main.c lista.c

clean:
	rm -f minigit minigit.exe
