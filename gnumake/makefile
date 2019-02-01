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
all:
	@echo $(OBJPATH)
csrc := $(wildcard *.c) $(wildcard *.cpp)
$(warning $(csrc))
foo: %.c 
	@echo  "creating foo [$*]"
