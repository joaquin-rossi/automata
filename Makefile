CC=gcc
CFLAGS=-Wall
LDFLAGS=-lSDL2

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, src/%.o, $(SRC))
BIN=automata

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BIN) $(OBJ)
