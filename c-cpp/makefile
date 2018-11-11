objects = array.o array1.o
CC = gcc
CXX = g++
CFLAGS = -g
all: array array1
array1: array1.o
	$(CC) -g -o array1 $<
array: array.o
	$(CC) -g -o array $<
$(objects): %.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
.PHONY: clean all
clean:
	@rm array array1 $(objects) 

