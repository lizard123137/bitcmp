TARGET = bitcmp

CC = gcc
CFLAGS = -Wall -O3

$(TARGET): src/main.c
	$(CC) $^ -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)
