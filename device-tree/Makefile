CC = gcc

.PHONY: all

all: pled

pled: pled.c
	$(CROSS_COMPILE)$(CC) pled.c $(LIB_FLAGS) -Wall -o $@
