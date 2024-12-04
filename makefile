CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

SRCS = main.c gameLoop.c
HEADERS = gameLoop.h
OBJS = $(SRCS:.c=.o)
TARGET = wordle-game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)