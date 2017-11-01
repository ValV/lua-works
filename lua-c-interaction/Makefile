# Makefile

CC=gcc
CFLAGS=
LDFLAGS=-llua

BIN=lci
LUA=script.lua

all: $(BIN)

run: all
	@eval ./$(BIN) $(LUA)

.PHONY: clean

clean:
	@rm -fv $(BIN)
