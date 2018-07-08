CC:=gcc
CFLAGS:=-Wall -g -std=c99

targets = rpn-calc
all: $(targets)

rpn-calc: rpn_calc.o stack.o stack.h Makefile
	$(CC) $(CFLAGS) $(filter %.o,$^) -o $@

clean:
	@rm *.o *~ $(targets) -f
