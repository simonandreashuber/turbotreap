# Makefile for a simple C program

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -O3

# Source files and the executable name
SRCS = main.c turbotreap.c 
TARGET = main

# Default target
all: $(TARGET)

# Compile the source files and generate the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean the build artifacts
clean:
	rm -f $(TARGET)

.PHONY: all clean

