Server:= Server.o
Client:= Client.o

CC = g++

CFLAGS = -std=c++11 -g -Wall

all: Server Client User.o

a: $(Server) User.o
	$(CC) $(CFLAGS) -o$@ $^

b: $(Client)
	$(CC) $(CFLAGS) -o$@ $^

%.o: %.c
	g++ -c -o$@ $<

clean:
	rm -f *.o

.PHONY: all clean
