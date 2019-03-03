csrc=$(wildcard *.c)
cxxsrc=$(wildcard *.cpp)
cobjects = $(csrc:%.c=%.o) 
cppobjects = $(cxxsrc:%.cpp=%.o)

#$(warning $(csrc))
#$(warning $(cxxsrc))
#$(warning $(cobjects))
#$(warning $(cppobjects))
CC = gcc
CXX = g++
CFLAGS := -g
CXXFLAGS := -g
PGMs=fmtprt practice1
all: $(PGMs)

fmtprt: fmtprt.o
	$(CXX) -o $@ $<
practice1: practice1.o 
	$(CXX) -o $@ $<


# strlval: strlvalue.o
# 	$(CXX) $(CFLAGS) -o $@ $<
$(cobjects):%.o:%.c
	$(CC) $(CFLAGS) -c $<
$(cppobjects):%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: all clean
clean:
	-@rm -f *.o $(PGMs)

