CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g -Isrc
LDFLAGS =

VPATH = src src/hashmap src/tokenizer src/expression src/vector src/string\
		src/expression/tokens

all: myfind

# GENERATE My Find
OBJS_TOKENS = action_print.o operator_and.o operator_or.o test_name.o\
			  test_type.o action_exec.o action_execdir.o
OBJS = 	myfind.o hash_map.o tokenizer.o tokparsing.o expression.o util.o\
		options.o vector.o cmdline.o options.o ast.o file_explorer.o\
		string.o stream.o search.o
OBJS += $(OBJS_TOKENS)

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
	$(RM) -r myfind $(OBJS) $(TESTS_LOG)