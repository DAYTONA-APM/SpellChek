CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O2 -std=c89 -pedantic

LIB_NAME = src/libtree.so
BENCH_NAME = src/benchmark
SRCS = src/tree.c src/words.c

.PHONY: all clean test

all: $(LIB_NAME) $(BENCH_NAME)

$(LIB_NAME): $(SRCS)
	$(CC) $(CFLAGS) -shared $(SRCS) -o $(LIB_NAME)

$(BENCH_NAME): $(SRCS) src/benchmark.c
	$(CC) $(CFLAGS) src/benchmark.c $(SRCS) -o $(BENCH_NAME)

clean:
	rm -f $(LIB_NAME) $(BENCH_NAME)

