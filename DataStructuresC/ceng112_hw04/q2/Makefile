CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = table-manager
all: $(targets)

table-manager: table_manager.o table.o table.h Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
