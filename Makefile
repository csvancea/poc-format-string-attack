CFLAGS =
LDFLAGS =

all: poc

poc: poc.o

.PHONY: clean
clean:
	rm -f poc *.o
