Server:= Server.o
Client:= Client.o

all: Server Client

a: $(Server)
	g++ -o$@ $^

b: $(Client)
	g++ -o$@ $^

%.o: %.c
	g++ -c -o$@ $<

clean:
	rm -f *.o

.PHONY: all clean
