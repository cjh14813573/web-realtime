CFLAGS=-g -Wall
CC=arm-linux-gcc
AR=arm-linux-ar
RANLIB=arm-linux-ranlib
LIBS=-L./ -lcgic

all: libcgic.a realtime.cgi

install: libcgic.a
	cp libcgic.a /usr/local/lib
	cp cgic.h /usr/local/include
	@echo libcgic.a is in /usr/local/lib. cgic.h is in /usr/local/include.

libcgic.a: cgic.o cgic.h
	rm -f libcgic.a
	$(AR) rc libcgic.a cgic.o
	$(RANLIB) libcgic.a

realtime.cgi: realtime.o libcgic.a inifile.o
	$(CC) realtime.o inifile.o  -o realtime.cgi ${LIBS}

clean:
	rm -f *.o *.a realtime.cgi

test:
	$(CC) -D UNIT_TEST=1 cgic.c -o cgicunittest
	./cgicunittest
