CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = graph-traverse
all: $(targets)

graph-traverse: graph_traverse.o queue.o queue.h Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
