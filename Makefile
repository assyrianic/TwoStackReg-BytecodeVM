all: main

CC = gcc
override CFLAGS += -s -O2 -mtune=native -march=native -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)

main: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@"

main-debug: $(SRCS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug
