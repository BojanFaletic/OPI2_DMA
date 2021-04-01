.PHONY: clean run help build check
.DEFAULT_GOAL := check
.SILENT:

### FILE STRUCTURE ###
PROJECT=main

SRC_FILES = $(wildcard src/*.cpp)
OBJ_FILES :=  $(patsubst src/%.cpp,build/obj/%.o,$(SRC_FILES))
HEADERS = $(wildcard src/*.hpp)

PROJ_OBJ = build/obj/$(PROJECT).o


### COMPILER FLAGS ###
CC_PATH=/tools/SDK/2018.2/gnu/aarch32/lin/gcc-arm-linux-gnueabi/bin/
CC=$(CC_PATH)arm-linux-gnueabihf-g++
LDFLAGS=
CPPFLAGS=--std=c++17 -I./header -O0
CXXFLAGS:=$(CXXFLAGS) -Werror -Wall -Wextra -Wconversion -Wunreachable-code \
	-Wuninitialized -pedantic-errors -Wold-style-cast -Wno-error=unused-variable -Wunused


check:
	make clean
	make build

build: build/dma

run: build/dma
	scp build/dma bojan@orangepi:~/driver/dma/out/test

clean:
	rm -f build/obj/* build/dma

summary:
	wc -l $(PROJECT).cpp src/* header/*

help:
	@echo "** HELP **"
	@echo "make run: build && run program"
	@echo "make check: build && run test"
	@echo "make summary: count number of lines in libs and src"
	@echo "make build: combile project"
	@echo "make clean: remove all object files"


### TUTORIAL ON MAKE
# This is how Makefile works
# all: library.cpp main.cpp
# $@ evaluates to all
# $< evaluates to library.cpp
# $^ evaluates to library.cpp main.cpp

# build project
build/dma: $(PROJ_OBJ) $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^


build/obj/%.o: src/%.cpp
	echo "Building $< --> $@"
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

build/obj/main.o: main.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
