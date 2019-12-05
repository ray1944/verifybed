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
CFLAGS = -g
CXXFLAGS = -g -std=c++11 -Wc++11-extensions -I$(BOOST_INCLUDE) 
LINKFLAGS = -g 
LNKLIBS := 
PGMs=memmov wrap-enum genran refofarr objincon iobasic cpp_basics1 map_basic1 \
     findinmap refaddr constmemfunc rvsitr rvsitr1 num_str getsystime stdstream \
	  inoutiterator c11features machinfo versionstr cpstrtochararray 
all: $(PGMs)

memmov: memmov.o
	$(CC) $(LINKFLAGS) -o memmov $<
wrap-enum: wrap-enum.o
	$(CXX) $(LINKFLAGS) -o wrap-enum $<
genran: genrandom.o 
	$(CXX) $(LINKFLAGS) -o genran $<
refofarr: refofarr.o
	$(CXX) $(LINKFLAGS) -o refofarr $<
objincon: objincontainer.o
	$(CXX) $(LINKFLAGS) -o objincon $<
iobasic: iobasic.o
	$(CXX) $(LINKFLAGS) -o $@ $<
cpp_basics1: cpp_basics1.o
	$(CXX) $(LINKFLAGS) -o $@ $<
map_basic1: map_basic1.o 
	$(CXX) $(LINKFLAGS) -o $@ $<
findinmap: findinmap.o
	$(CXX) $(CFLAGS) -o $@ $<
nrand: nrand.o
	$(CXX) $(CFLAGS) -o $@ $<

# strlval: strlvalue.o
# 	$(CXX) $(CFLAGS) -o $@ $<
$(cobjects):%.o:%.c
	$(CC) $(CFLAGS) -c $<
$(cppobjects):%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $<
	
#%.o: %.c
#	@echo "compiling [$*]"
#	$(CC) $(CFLAGS) -o $@ -c $<
#%.o: %.cpp
#	@echo "compiling c++ [$*]"
#	$(CXX) $(CFLAGS) -o $@ -c $<

.PHONY: all clean
clean:
	-@rm -f *.o $(PGMs)

