CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -O3 -g

TARGET = calculator

OBJS = main.o utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h 
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm $(TARGET) $(OBJS)