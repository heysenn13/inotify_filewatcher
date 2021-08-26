# for C++ define  CC = g++
CC = gcc

# define any compile-time flags
CFLAGS = -Wall -g

SRC    = $(wildcard *.c)
OBJS   = $(SRC:%.c=%.o)
TARGET = watcher

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

all:	$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)
