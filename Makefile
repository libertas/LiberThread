
all:test

test:examples/test.c liberthread.h
	cp examples/test.c .
	$(CC) -o test test.c

.PHONY:clean
clean:
	rm test
