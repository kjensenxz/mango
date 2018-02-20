.SUFFIXES: .c .o

PREFIX = /usr/local/

CC = gcc

VERSION = v2.1.6

CFLAGS = --std=c11 -Wall -Werror -DVERSION=\"$(VERSION)\" -O2 -Wpedantic
LDFLAGS = 

SRC = mango.c libmango.c util.c
OBJ = $(SRC:.c=.o)
INC = libmango.h util.h
BIN = mango

DIST = $(BIN)-$(VERSION)

all: options $(BIN)

options: 
	@echo "BINARY  = $(BIN)"
	@echo "CFLAGS  = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo "CC      = $(CC)"
	@echo "PREFIX  = $(PREFIX)"

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LDFLAGS)
	strip -s $@


clean:
	rm -f $(BIN) $(OBJ) $(BIN)-$(VERSION).tar.gz

dist: all
	mkdir -p $(DIST)/
	cp -R $(BIN) LICENSE.md Makefile README.md $(SRC) $(INC) $(DIST)/
	tar -cf - $(DIST) | gzip > $(DIST).tar.gz

distclean: clean
	rm -rf $(DIST)/ $(DIST).tar.gz

install: all
	mkdir -p $(PREFIX)/bin/
	cp -f $(BIN) $(PREFIX)/bin/
	chmod 755 $(PREFIX)/bin/$(BIN)

uninstall:
	rm -f $(PREFIX)/bin/$(BIN)

.PHONY: all options distclean clean install uninstall
