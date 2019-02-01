csrc=memmov.c
cxxsrc=wrap-enum.cpp genrandom.cpp refofarr.cpp
cobjects = $(csrc:%.c=%.o) 
cppobjects = $(cxxsrc:%.cpp=%.o)

#$(warning $(csrc))
#$(warning $(cxxsrc))
#$(warning $(cobjects))
#$(warning $(cppobjects))
CC = gcc
CXX = g++
CFLAGS = -g
all: memmov wrap-enum genran refofarr
memmov: memmov.o
	$(CC) $(CFLAGS) -o memmov $<
wrap-enum: wrap-enum.o
	$(CXX) $(CFLAGS) -o wrap-enum $<
genran: genrandom.o 
	$(CXX) $(CFLAGS) -o genran $<
refofarr: refofarr.o
	$(CXX) $(CFLAGS) -o refofarr $<
$(cobjects):%.o:%.c
	$(CC) -g -c $<
$(cppobjects):%.o:%.cpp
	$(CXX) -g -c $<
	
%.o: %.c
	@echo "compiling [$*]"
	$(CC) $(CFLAGS) -o $@ -c $<
%.o: %.cpp
	@echo "compiling c++ [$*]"
	$(CXX) $(CFLAGS) -o $@ -c $<

.PHONY: all clean
clean:
	-rm *.o memmov wrap-enum genran refofarr

