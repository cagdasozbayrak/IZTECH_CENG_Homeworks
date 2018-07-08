CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = deque-test
all: $(targets)

deque-test: deque_test.o deque.o deque.h Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
