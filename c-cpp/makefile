csrc=memmov.c
cxxsrc=wrap-enum.cpp genrandom.cpp
cobjects = $(csrc:%.c=%.o) 
cppobjects = $(cxxsrc:%.cpp=%.o)

#$(warning $(csrc))
#$(warning $(cxxsrc))
#$(warning $(cobjects))
#$(warning $(cppobjects))
CC = gcc
CXX = g++
CFLAGS = -g
all: memmov wrap-enum genran
memmov: memmov.o
	$(CC) $(CFLAGS) -o memmov $<
wrap-enum: wrap-enum.o
	$(CXX) $(CFLAGS) -o wrap-enum $<
genran: genrandom.o 
	$(CXX) $(CFLAGS) -o genran $<
$(cobjects):%.o:%.c
	$(CC) -g -c $<
$(cppobjects):%.o:%.cpp
	$(CXX) -g -c $<
	

.PHONY: clean all
clean:
	-rm *.o memmov wrap-enum genran

