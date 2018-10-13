CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g -Isrc
LDFLAGS =

VPATH = src src/hashmap src/tokenizer src/expression src/vector

all: myfind

# GENERATE My Find
OBJS = 	myfind.o hash_map.o tokenizer.o tokparsing.o expression.o util.o\
		options.o vector.o cmdline.o options.o ast.o file_explorer.o

myfind: $(OBJS)

# Launch test suite
CHECK_SCRIPT = tests/check.sh
TESTS_FOLDER = $(CURDIR)/tests/cmds_to_test
BIN_TO_TEST = $(CURDIR)/myfind
TESTS_LOG = $(CURDIR)/tests/logs

check: myfind
	$(CHECK_SCRIPT) $(TESTS_FOLDER) $(BIN_TO_TEST) $(TESTS_LOG)

# CLEAN
clean:
	$(RM) -r myfind $(OBJS)