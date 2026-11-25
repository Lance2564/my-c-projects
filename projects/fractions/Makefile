CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -O3 -g

TARGET = fraction

OBJS = main.o functions.o

all: $(TARGET)

$(TARGET) : $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

main.o : main.c
	@$(CC) $(CFLAGS) -c main.c

functions.o: functions.c functions.h
	@$(CC) $(CFLAGS) -c functions.c

clean:
	@rm $(OBJS) $(TARGET)