# Compiler configuration
CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O2

# Target shared library name
LIB_NAME = src/libtree.dylib

# Source files needed for the backend engine
SRCS = src/tree.c src/words.c

.PHONY: all clean

# Default target
all: $(LIB_NAME)

# Compile the shared library from the C source files
$(LIB_NAME): $(SRCS)
	$(CC) $(CFLAGS) -shared $(SRCS) -o $(LIB_NAME)

# Remove build artifacts to force a fresh compilation
clean:
	rm -f $(LIB_NAME)

