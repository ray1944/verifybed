csrc=memmov.c
cxxsrc=wrap-enum.cpp
cobjects = $(csrc:%.c=%.o) 
cppobjects = $(cxxsrc:%.cpp=%.o)

#$(warning $(csrc))
#$(warning $(cxxsrc))
#$(warning $(cobjects))
#$(warning $(cppobjects))
CC = gcc
CXX = g++
CFLAGS = -g
all: memmov wrap-enum
memmov: memmov.o
	$(CC) -g -o memmov $<
wrap-enum: wrap-enum.o
	$(CXX) -g -o wrap-enum $<
$(cobjects):%.o:%.c
	$(CC) -g -c $<
$(cppobjects):%.o:%.cpp
	$(CXX) -g -c $<
	

.PHONY: clean all
clean:
	-rm *.o memmov wrap-enum

