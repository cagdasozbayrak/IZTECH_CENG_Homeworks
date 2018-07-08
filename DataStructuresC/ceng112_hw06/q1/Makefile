CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = rb-tree
all: $(targets)

rb-tree: rb_tree.o student.h Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
