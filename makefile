CC=gcc
FLAGS= -Wall -g

all: main

main: main.o nodes.o edges.o algo.o
	$(CC) $(FLAGS) -o $@ $^

nodes.o: nodes.c nodes.h
	$(CC) $(FLAGS) -c $<

edges.o: edges.c edges.h
	$(CC) $(FLAGS) -c $<

algo.o: algo.c algo.h
	$(CC) $(FLAGS) -c $<

main.o: main.c nodes.h edges.h algo.h
	$(CC) $(FLAGS) -c $<

.PHONY: c clean all

c: clean

clean:
	rm -f *.o 