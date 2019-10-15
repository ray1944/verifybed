csrc=$(wildcard *.c)
# cxxsrc=wrap-enum.cpp genrandom.cpp refofarr.cpp objincontainer.cpp
cxxsrc=$(wildcard *.cpp)
cobjects = $(csrc:%.c=%.o) 
cppobjects = $(cxxsrc:%.cpp=%.o)

CC = gcc
CXX = g++
CFLAGS = -g 
CXXFLAGS = -g -DLIBICONV_PLUG
LINKFLAGS = -g -L/use/lib -liconv
LNKLIBS := 
PGMs=useiconv
all: $(PGMs)

useiconv: useiconv.o
	$(CXX) $(LINKFLAGS) -o useiconv $<


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

