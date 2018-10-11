CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g -fsanitize=address -Isrc
LDFLAGS = -fsanitize=address -L.

VPATH = src src/hashmap src/tokenizer

all: myfind

# GENERATE My Read Iso
OBJS = myfind.o hash_map.o tokenizer.o tokparsing.o

#.PHONY: myreadiso
myfind: $(OBJS)

# CLEAN
clean:
	$(RM) -r myfind $(OBJS)
