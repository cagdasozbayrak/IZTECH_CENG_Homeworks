CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = sort-selection
all: $(targets)

sort-selection: sort_selection.o Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
