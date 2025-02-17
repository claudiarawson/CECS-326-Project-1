# Compiler Used
CC = gcc

# Compiler flags (POSIX for Windows & C Compatability)
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L

# Name of the executable file
TARGET = filecopy
INPUT = input.txt
OUTPUT = copy.txt

# Default Rule: Compile the program
$(TARGET): FileCopy.c
	$(CC) $(CFLAGS) -o $(TARGET) FileCopy.c

# Run Rule: Run the program with specified input and output files
run: $(TARGET)
	./$(TARGET) $(INPUT) $(OUTPUT)

# Clean Rule: Remove output file
clean:
	rm -f $(TARGET) $(OUTPUT)
