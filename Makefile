CC=gcc
CFLAGS=-Wall -lSDL2

SRC=src
OBJ=obj
BIN=bin
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINS=$(BIN)/main

all: $(BINS)

$(BINS): $(OBJS)
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BIN)/* $(OBJ)/*