# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable name
TARGET = shell

# Default target
all: $(TARGET)

# Compile the shell
$(TARGET): shell.c
	$(CC) $(CFLAGS) -o $(TARGET) shell.c

# Clean up compiled files
clean:
	rm -f $(TARGET)
