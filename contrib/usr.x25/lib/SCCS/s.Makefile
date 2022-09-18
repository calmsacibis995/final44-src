h02033
s 00006/00023/00002
d D 5.2 91/04/29 18:38:58 sklower 2 1
c use new BSD paradigm
e
s 00025/00000/00000
d D 5.1 90/09/03 19:00:02 sklower 1 0
c date and time created 90/09/03 19:00:02 by sklower
e
u
U
t
T
I 1
D 2
CFLAGS = -O
E 2
I 2
#	%W% (Berkeley) %G%
E 2

D 2
SOURCES = x25err.c getx25hostent.c getx25hostbyname.c getx25hostbyaddr.c ccitt_addr.c print.c verify.c
E 2
I 2
LIB=	x25
SRCS=	ccitt_addr.c getx25hostbyaddr.c getx25hostbyname.c getx25hostent.c \
	print.c verify.c x25err.c
MAN3=	
E 2

D 2
OBJECTS = x25err.o getx25hostent.o getx25hostbyname.o getx25hostbyaddr.o ccitt_addr.o print.o verify.o

HEADERS = /sys/netccitt/x25.h ../h/x29.h

x25lib.a: $(OBJECTS)
	ar rv x25lib.a $?
	ranlib x25lib.a

install: x25lib.a
	install x25lib.a /usr/lib/libx25.a
	ranlib /usr/lib/libx25.a

.c.o:
	cc -c $(CFLAGS) $*.c


$(OBJECTS): $(HEADERS)

clean:
	rm -f core *.o *.CKP .emacs_*

E 2
I 2
.include <bsd.lib.mk>
E 2
E 1
