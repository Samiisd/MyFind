CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g -fsanitize=address -Isrc
LDFLAGS = -fsanitize=address -L.

VPATH = src

all: myfind

# GENERATE My Read Iso
OBJS =

#.PHONY: myreadiso
myfind: $(OBJS)

# CLEAN
clean:
	$(RM) -r myfind $(OBJS)
