csrc=$(wildcard *.c)
# cxxsrc=wrap-enum.cpp genrandom.cpp refofarr.cpp objincontainer.cpp
cxxsrc=$(wildcard *.cpp)
cobjects = $(csrc:%.c=%.o) 
cppobjects = $(cxxsrc:%.cpp=%.o)

#$(warning $(csrc))
#$(warning $(cxxsrc))
#$(warning $(cobjects))
#$(warning $(cppobjects))
CC = gcc
CXX = g++
CFLAGS = -g
PGMs=memmov wrap-enum genran refofarr objincon iobasic cpp_basics1 map_basic1
all: $(PGMs)

memmov: memmov.o
	$(CC) $(CFLAGS) -o memmov $<
wrap-enum: wrap-enum.o
	$(CXX) $(CFLAGS) -o wrap-enum $<
genran: genrandom.o 
	$(CXX) $(CFLAGS) -o genran $<
refofarr: refofarr.o
	$(CXX) $(CFLAGS) -o refofarr $<
objincon: objincontainer.o
	$(CXX) $(CFLAGS) -o objincon $<
iobasic: iobasic.o
	$(CXX) $(CFLAGS) -o $@ $<
cpp_basics1: cpp_basics1.o
	$(CXX) $(CFLAGS) -o $@ $<
map_basic1: map_basic1.o 
	$(CXX) $(CFLAGS) -o $@ $<

# strlval: strlvalue.o
# 	$(CXX) $(CFLAGS) -o $@ $<
$(cobjects):%.o:%.c
	$(CC) -g -c $<
$(cppobjects):%.o:%.cpp
	$(CXX) -g -c $<
	
#%.o: %.c
#	@echo "compiling [$*]"
#	$(CC) $(CFLAGS) -o $@ -c $<
#%.o: %.cpp
#	@echo "compiling c++ [$*]"
#	$(CXX) $(CFLAGS) -o $@ -c $<

.PHONY: all clean
clean:
	-@rm -f *.o $(PGMs)

