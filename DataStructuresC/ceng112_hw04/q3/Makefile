CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = registery
all: $(targets)

registery: registery.o Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
