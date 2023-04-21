LIB_NAME = arith
APP_NAME = demoApp

LIB_PATH = lib
INC_PATH = include

OBJ = lib/libarith.so include/libarith.h main.c io.c io.h
CFLAGS = -Wall -Llib -larith
CFLAGS_PIC = -c -Wall -Werror -fpic
CFLAGS_SO = -shared

.PHONY: all install clean

all: $(OBJ)
	gcc -o demo main.c io.c $(CFLAGS)

lib/libarith.so: lib/arith.o
	gcc $(CFLAGS_SO) -o lib/libarith.so lib/arith.o

lib/arith.o: lib/arith.c
	gcc $(CFLAGS_PIC) -o lib/arith.o lib/arith.c

install: lib/libarith.so include/libarith.h
	cp lib/libarith.so /usr/lib/
	cp include/libarith.h /usr/include

clean:
	rm -f lib/libarith.so lib/arith.o demo
	rm -f /usr/lib/libarith.so /usr/include/libarith.h
