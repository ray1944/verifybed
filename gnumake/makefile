CURLIB=abc
PROJECTDIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
$(info $(PROJECTDIR))
PROJECTDIR := $(realpath $(shell pwd))
$(info $(PROJECTDIR))
LASTWORD = $(lastword foo bar)
$(warning $(LASTWORD))
$(info project dir:$(PROJECTDIR))
OBJLIB := $(basename $(notdir $(PROJECTDIR)))
$(warning $(OBJLIB))
$(warning $(realpath main.c auth.c))
CSRC=$(wildcard *.c)
$(warning $(CSRC))
extract = $(suffix src/foo.c src-1.0/bar.c hacks)
$(warning $(extract))
csrc := $(wildcard *.c) $(wildcard *.cpp)
$(warning $(csrc))
all: 
	@echo $(OBJPATH)

foo: $(csrc) 
	@echo  "所有依赖目标的集合 [$+] + [$^]"
	@echo  "第一个依赖集 [$<]"
	@echo  "目标集 [$@]"
	@echo  "所有比目标新的依赖目标的集合[$?]"
	@echo  "目标模式中%及其之前的部分 [$*]"
	@echo  "仅当目标是函数库文件中，表示规则中的目标成员名 [$%]"

cmod := $(wildcard *.c)
cppmod := $(wildcard *.cpp)
%.PGM: $(cmod)
	@echo "[$^]"

%.PGM: $(cppmod)
	@echo "[$+]"
