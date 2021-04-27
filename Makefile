CC=gcc
CFLAGS=-Wall

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))
BIN=bin/main

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p bin/
	$(CC) $(CFLAGS) $(OBJ) -o $@

obj/%.o: src/%.c
	mkdir -p obj/
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r bin/* obj/*
