
# automates compiling the Student Registry project
CC = gcc
CFLAGS = -Wall -g

# Final program name
TARGET = student_registry

# Object files needed to build the target
OBJS = student_registry.o main.o

# Default target: build the program
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile student_registry.c into student_registry.o
student_registry.o: student_registry.c student_registry.h
	$(CC) $(CFLAGS) -c student_registry.c

# Compile main.c into main.o
main.o: main.c student_registry.h
	$(CC) $(CFLAGS) -c main.c

# Build and immediately run the program
run: all
	./$(TARGET)

# Remove compiled files (start clean)
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean