CC = gcc # The compiler(GCC)
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g -lm # My flags

TARGET = bank # Final name of the executable

OBJS = main.o account.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiles main.c into main.o
main.o: main.c account.h
	$(CC) $(CFLAGS) -c main.c

# Compiles account.c into account.o
account.o: account.c account.h
	$(CC) $(CFLAGS) -c account.c

# Cleans up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)