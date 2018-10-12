CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g -Isrc
LDFLAGS =

VPATH = src src/hashmap src/tokenizer src/expression src/vector

all: myfind

# GENERATE My Read Iso
OBJS = 	myfind.o hash_map.o tokenizer.o tokparsing.o expression.o util.o\
		options.o vector.o cmdline.o options.o

#.PHONY: myreadiso
myfind: $(OBJS)

# CLEAN
clean:
	$(RM) -r myfind $(OBJS)