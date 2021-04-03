.PHONY: clean run help build check test
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

# for testing
#CXXFLAGS= -Wall -Wextra


# COMMANDS
CLEAN=rm -f build/obj/*.o build/dma test/*.o test/main

check:
	$(CLEAN)
	make build CC=clang++ -j8
	$(CLEAN)

test:
	$(CLEAN)
	make -s test/main CC=clang++ -j8
	./test/main

test/main: build/obj/test_main.o $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

build:
	make -s build/dma -j8

run: build/dma
	scp build/dma bojan@orangepi:~/driver/dma/out/test

clean:
	$(CLEAN)

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
	echo "$< -> $@"
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

build/obj/main.o: main.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

build/obj/test_main.o: test/main.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<