
all:test

test:test.c liberthread.h
	$(CC) -o test test.c

.PHONY:clean
clean:
	rm test
