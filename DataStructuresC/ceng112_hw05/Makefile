CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = patients
all: $(targets)

pqueue: patients.o Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
