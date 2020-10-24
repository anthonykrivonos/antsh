CC = gcc
CXX = g++

INCLUDES =

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g

LDLIBS =

antsh: antsh.o

antsh.o: antsh.c

.PHONY: clean
clean:
	rm -f *.o a.out core antsh

.PHONY: all
all: clean antsh

