CC=gcc
OBJECTS_MAIN=main.o edges.o nodes.o graph.o brute.o
FLAGS= -Wall -g
EXE=graph

#target commands
all: $(EXE)
$(EXE): $(OBJECTS_MAIN) 
	$(CC) $(OBJECTS_MAIN) -o $(EXE)
edges.o: edges.c graph.h
	$(CC) $(FLAGS) -c edges.c
nodes.o: nodes.c graph.h
	$(CC) $(FLAGS) -c nodes.c
graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c
main.o: main.c edges.c nodes.c graph.c brute.c graph.h 
	$(CC) $(FLAGS) -c main.c 
	$(CC) $(FLAGS) -c brute.c 
.PHONY: clean all
clean:
	rm -f *.o *.a *.so $(EXE)