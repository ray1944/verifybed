csrc=$(wildcard *.c)
# cxxsrc=wrap-enum.cpp genrandom.cpp refofarr.cpp objincontainer.cpp
cxxsrc=$(wildcard *.cpp)
cobjects = $(csrc:%.c=%.o) 
cppobjects = $(cxxsrc:%.cpp=%.o)

#$(warning $(csrc))
#$(warning $(cxxsrc))
#$(warning $(cobjects))
#$(warning $(cppobjects))
BOOST_INCLUDE = /Users/ray1944/workspace/aldon/src/boost_1_55/
CC = gcc
CXX = g++
CFLAGS = -g -I$(BOOST_INCLUDE)
CXXFLAGS = -g
LNKLIBS := 
PGMs=memmov wrap-enum genran refofarr objincon iobasic cpp_basics1 map_basic1 \
     findinmap refaddr constmemfunc rvsitr rvsitr1 num_str getsystime
all: $(PGMs)

memmov: memmov.o
	$(CC) $(CXXFLAGS) -o memmov $<
wrap-enum: wrap-enum.o
	$(CXX) $(CXXFLAGS) -o wrap-enum $<
genran: genrandom.o 
	$(CXX) $(CXXFLAGS) -o genran $<
refofarr: refofarr.o
	$(CXX) $(CXXFLAGS) -o refofarr $<
objincon: objincontainer.o
	$(CXX) $(CXXFLAGS) -o objincon $<
iobasic: iobasic.o
	$(CXX) $(CXXFLAGS) -o $@ $<
cpp_basics1: cpp_basics1.o
	$(CXX) $(CXXFLAGS) -o $@ $<
map_basic1: map_basic1.o 
	$(CXX) $(CXXFLAGS) -o $@ $<
findinmap: findinmap.o
	$(CXX) $(CXXFLAGS) -o $@ $<
refaddr: refaddr.o
	$(CXX) $(CXXFLAGS) -o $@ $<
constmemfunc: constmemfunc.o
	$(CXX) $(CXXFLAGS) -o $@ $<
rvsitr: rvsitr.o
	$(CXX) $(CXXFLAGS) -o $@ $<
rvsitr1: rvsitr1.o
	$(CXX) $(CXXFLAGS) -o $@ $<
num_str: num_str.o
	$(CXX) $(CXXFLAGS) -o $@ $<
getsystime: getsystime.o 
	$(CXX) $(CXXFLAGS) -o $@ $<

# strlval: strlvalue.o
# 	$(CXX) $(CFLAGS) -o $@ $<
$(cobjects):%.o:%.c
	$(CC) $(CFLAGS) -c $<
$(cppobjects):%.o:%.cpp
	$(CXX) $(CFLAGS) -c $<
	
#%.o: %.c
#	@echo "compiling [$*]"
#	$(CC) $(CFLAGS) -o $@ -c $<
#%.o: %.cpp
#	@echo "compiling c++ [$*]"
#	$(CXX) $(CFLAGS) -o $@ -c $<

.PHONY: all clean
clean:
	-@rm -f *.o $(PGMs)

