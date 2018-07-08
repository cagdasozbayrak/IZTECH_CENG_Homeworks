CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = rand-uniq
all: $(targets)

rand-uniq: rand_uniq.o set_of_ints.o set_of_ints.h Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
