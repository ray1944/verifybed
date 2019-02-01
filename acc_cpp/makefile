#csrc=xxx.c
cxxsrc=$(wildcard *.cpp)
#cobjects = $(csrc:%.c=%.o) 
cppobjects = $(cxxsrc:%.cpp=%.o)

#$(warning $(csrc))
#$(warning $(cxxsrc))
#$(warning $(cobjects))
#$(warning $(cppobjects))
CC = gcc
CXX = g++
CFLAGS = -g
all: fmtprt 
fmtprt: fmtprt.o
	$(CXX) -g -o fmtprt $<

#$(cobjects):%.o:%.c
#	$(CC) -g -c $<
$(cppobjects):%.o:%.cpp
	$(CXX) -g -c $<
	

.PHONY: clean all
clean:
	-rm *.o fmtprt

