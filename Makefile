CC = cland
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = 

main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LDFLAGS)
