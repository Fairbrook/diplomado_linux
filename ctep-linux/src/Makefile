LIB_NAME = arith
APP_NAME = demoApp

LIB_PATH = lib
INC_PATH = include

OBJ = lib/libarith.so main.c io.c io.h
CFLAGS = -Wall -Llib -larith
CFLAGS_PIC = -c -Wall -Werror -fpic
CFLAGS_SO = -shared

.PHONY: all install clean

all: $(OBJ)
	gcc $(CFLAGS) -o demo main.c	

lib/libarith.so: lib/arith.o
	gcc $(CFLAGS_SO) -o lib/libarith.so lib/arith.o

lib/arith.o: lib/arith.c
	gcc $(CFLAGS_PIC) -o lib/arith.o lib/arith.c

install: lib/libarith.so include/libarith.h
	cp lib/libarith.so /usr/lib/
	cp lib/libarith.h /usr/include

clean:
	rm -f lib/libarith.so lib/arith.o
	rm -f /usr/lib/libarith.so /usr/include/libarith.h
